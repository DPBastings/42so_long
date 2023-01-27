/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_read.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:20:41 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/27 14:36:18 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int		check_ext(char const *filename, char const *extension);
static t_list	*get_list(int fd, size_t *width, size_t *height);
static void		lst_destroy(t_list **list);
static int		populate_map(t_map *map, t_list *list);

static int	check_ext(char const *filename, char const *extension)
{
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (len < ext_len + 1)
		return (0);
	return ((int) ft_strnstr(filename + len - ext_len, extension, ext_len));
}

static t_list	*get_list(int fd, size_t *width, size_t *height)
{
	t_list	*list;
	char	*slice;

	list = NULL;
	*height = 0;
	slice = ft_getline(fd);
	*width = ft_strlen(slice);
	while (slice)
	{
		if (ft_strlen(slice) != *width)
		{
			free(slice);
			return (ft_lstclear(&list, free), NULL);
		}
		ft_lstadd_back(&list, ft_lstnew(slice));
		(*height)++;
		slice = ft_getline(fd);
	}
	(*width)--;
	return (list);
}

static void	lst_destroy(t_list **list)
{
	t_list	*prev;

	while (*list)
	{
		prev = *list;
		*list = (*list)->next;
		free(prev);
	}
}

static int	populate_map(t_map *map, t_list *list)
{
	size_t	i;

	map->objs = malloc((map->h + 1) * sizeof(char *));
	if (map->objs == NULL)
		return (map_destroy(&map), 0);
	map->objs[map->h] = NULL;
	i = 0;
	while (list)
	{
		map->objs[i++] = list->content;
		list = list->next;
	}
	return (1);
}

#include "libftprintf.h"

t_map	*map_read(char const *filename)
{
	t_map	*map;
	t_list	*tmp;
	int		fd;

	if (!check_ext(filename, MAP_EXT))
	{
		ft_dprintf(2, "invalid filename\n");
		return (NULL);
	}
	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (map_destroy(&map), NULL);
	tmp = get_list(fd, &(map->w), &(map->h));
	close(fd);
	if (tmp == NULL)
		return (map_destroy(&map), NULL);
	populate_map(map, tmp);
	lst_destroy(&tmp);
	return (map);
}
