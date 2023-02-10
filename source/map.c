/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 11:42:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 18:07:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map.h"
#include "libft.h"
#include <stdlib.h>

#include "sl_test.h"

static unsigned int	chrtotype(char const chr);

t_map	*map_init(t_plane dims)
{
	t_map			*map;
	unsigned int	y;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->dims = dims;
	map->objs = ft_calloc(map->dims.h, sizeof(t_object **));
	if (map->objs == NULL)
		return (map_destroy(&map), NULL);
	y = 0;
	while (y < map->dims.h)
	{
		map->objs[y] = ft_calloc(map->dims.w, sizeof(t_object *));
		if (map->objs[y] == NULL)
			return (map_destroy(&map), NULL);
		y++;
	}
	map->none = object_init(OBJ_NONE);
	if (map->none == NULL)
		return (map_destroy(&map), NULL);
	return (map);
}

void	map_set(t_map *map, t_list *bytemap)
{
	t_point		p;
	t_object	*obj;
	char		*row;

	p.y = 0;
	while (p.y < map->dims.h)
	{
		p.x = 0;
		row = (char *)bytemap->content;
		while (p.x < map->dims.w)
		{
			if (row[p.x] != CHR_NONE)
			{	
				obj = object_init(chrtotype(row[p.x]));
				if (obj == NULL)
					sl_error(SL_MEMFAIL);	
				map->objs[p.y][p.x] = obj;
				obj->position = p;
			}
			p.x++;
		}
		bytemap = bytemap->next;
		p.y++;
	}
}

static unsigned int	chrtotype(char const chr)
{
	char *const	chars = CHR_ALL;
	char		*ptr;

	ptr = ft_strchr(chars, chr);
	if (ptr == NULL)
		sl_error(SL_INVMAP);
	return ((unsigned int)(ptr - chars));
}

t_object	**map_index(t_map *map, t_point p)
{
	if (p.y >= map->dims.h || p.x >= map->dims.w)
		return (&NOWHERE);
	return (&map->objs[p.y][p.x]);
}

void	map_destroy(t_map **map)
{
	t_point	p;

	p.y = 0;
	while (p.y < (*map)->dims.h)
	{
		p.x = 0;
		while (p.x < (*map)->dims.w)
		{
			object_destroy(&(*map)->objs[p.y][p.x]);
			p.x++;
		}
		free((*map)->objs[p.y]);
		p.y++;
	}
	free((*map)->objs);
	free((*map)->none);
	free(*map);
	*map = NULL;
}