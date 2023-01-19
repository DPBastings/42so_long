/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_read.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:20:41 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/09 15:41:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "libftprintf.h"

static void	slice_free(void *slice)
{
	free(slice);
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

static t_map	*get_map(t_list *list, size_t height)
{
	t_map	*map;
	size_t	i;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->size = height;
	map->objs = malloc((map->size + 1) * sizeof(char *));
	if (map->objs == NULL)
		return (free(map), NULL);
	map->objs[map->size] = NULL;
	i = 0;
	while (list)
	{
		map->objs[i++] = list->content;
		list = list->next;
	}
	return (map);
}

static t_list	*get_list(int fd, size_t *height)
{
	t_list	*list;
	char	*slice;
	size_t	width;

	list = NULL;
	*height = 0;
	slice = ft_getline(fd);
	width = ft_strlen(slice);
	while (slice)
	{
		if (ft_strlen(slice) != width)
		{
			*height = 0;
			free(slice);
			return (ft_lstclear(&list, slice_free), NULL);
		}
		ft_lstadd_back(&list, ft_lstnew(slice));
		(*height)++;
		slice = ft_getline(fd);
	}
	return (list);
}

t_map	*map_read(char const *filename)
{
	t_map	*map;
	t_list	*tmp;
	int		fd;
	size_t	height;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	tmp = get_list(fd, &height);
	close(fd);
	if (tmp == NULL)
		return (NULL);
	map = get_map(tmp, height);
	if (map == NULL)
		return (NULL);
	lst_destroy(&tmp);
	return (map);
}

void	map_destroy(t_map **map)
{
	char	**tmp;

	tmp = (*map)->objs;
	while (tmp)
	{
		free(*tmp);
		tmp++;
	}
	free((*map)->objs);
	free(*map);
	*map = NULL;
}
