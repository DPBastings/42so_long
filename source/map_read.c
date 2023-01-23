/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_read.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:20:41 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/23 18:21:35 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "libftprintf.h"

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

static int	get_map(t_map *map, t_list *list)
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

t_map	*map_read(char const *filename)
{
	t_map	*map;
	t_list	*tmp;
	int		fd;

	if (!check_filename(filename, ".ber", ft_strlen(filename)))
		return (NULL);
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
	get_map(map, tmp);
	lst_destroy(&tmp);
	return (map);
}
