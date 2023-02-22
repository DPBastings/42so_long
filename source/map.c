/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 11:42:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/20 13:07:28 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_check.h"

#include "libft.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static uint32_t	chrtotype(char const chr);
static bool		object_setup(t_map *map, t_point p, char type);

t_map	*map_init(t_plane dims)
{
	t_map		*map;
	uint32_t	y;

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
	map->none->obj_below = map->none;
	return (map);
}

void	map_set(t_map *map, t_list *bytemap)
{
	t_point		p;
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
				if (!object_setup(map, p, row[p.x]))
					sl_error(SL_MEMFAIL);
			}
			p.x++;
		}
		bytemap = bytemap->next;
		p.y++;
	}
}

static bool	object_setup(t_map *map, t_point p, char type)
{
	t_object	*obj;

	obj = object_init(chrtotype(type));
	if (obj == NULL)
		return (false);
	obj->obj_below = NOWHERE;
	object_place(obj, map, p);
	if (obj->type == OBJ_PLYR)
		map->player = obj;
	else if (obj->type == OBJ_EXIT)
		map->exit = obj;
	return (true);
}

static uint32_t	chrtotype(char const chr)
{
	char *const	chars = CHR_ALL;
	char		*ptr;

	ptr = ft_strchr(chars, chr);
	if (ptr == NULL)
		sl_error(SL_INVMAP);
	return ((uint32_t)(ptr - chars));
}

void	map_destroy(t_map **map)
{
	t_point		p;
	t_object	**slot;

	if (*map == NULL)
		return ;
	p.y = 0;
	while (p.y < (*map)->dims.h)
	{
		p.x = 0;
		while (p.x < (*map)->dims.w)
		{
			slot = map_index(*map, p);
			while (*slot)
				object_destroy(slot);
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
