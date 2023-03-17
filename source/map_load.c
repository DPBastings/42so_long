/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_load.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:20:41 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 13:14:38 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int		check_ext(char const *filename);
static t_list	*get_bytemap(int fd, t_upoint *dims);
static void		lst_destroy(t_list **list);
static int		open_file(char const *filename);

t_map	*map_load(char const *filename)
{
	t_map		*map;
	t_list		*bytemap;
	t_upoint	dims;
	int			fd;

	fd = open_file(filename);
	bytemap = get_bytemap(fd, &dims);
	close(fd);
	if (bytemap == NULL)
		sl_error(SL_MEMFAIL);
	map = map_init(dims);
	if (map == NULL)
		sl_error(SL_MEMFAIL);
	map_setup(map, bytemap);
	lst_destroy(&bytemap);
	return (map);
}

static int	open_file(char const *filename)
{
	int	fd;

	if (!check_ext(filename))
		sl_error(SL_INVEXT);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		sl_error(SL_INVPATH);
	return (fd);
}

static int	check_ext(char const *filename)
{
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(filename);
	ext_len = ft_strlen(SL_FILEEXT);
	if (len < ext_len + 1)
		return (0);
	if (ft_strnstr(filename + len - ext_len, SL_FILEEXT, ext_len))
		return (1);
	return (0);
}

static t_list	*get_bytemap(int fd, t_upoint *dims)
{
	t_list	*bytemap;
	char	*row;

	bytemap = NULL;
	dims->y = 0;
	row = ft_getline(fd);
	dims->x = ft_strlen(row);
	while (row)
	{
		if (ft_strlen(row) != dims->x)
		{
			free(row);
			ft_lstclear(&bytemap, free);
			sl_error(SL_INVMAP_DIMS);
		}
		ft_lstadd_back(&bytemap, ft_lstnew(row));
		dims->y++;
		row = ft_getline(fd);
	}
	dims->x--;
	return (bytemap);
}

static void	lst_destroy(t_list **list)
{
	t_list	*prev;

	while (*list)
	{
		prev = *list;
		*list = (*list)->next;
		free(prev->content);
		free(prev);
		prev = NULL;
	}
}
