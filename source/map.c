/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 11:42:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 17:07:44 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_object.h"
#include "sl_map_check.h"

#include "libft.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

t_map	*map_init(t_upoint dims)
{
	t_map		*map;
	uint32_t	y;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->dims = dims;
	map->objs = ft_calloc(map->dims.y, sizeof(t_object **));
	if (map->objs == NULL)
		return (map_destroy(&map), NULL);
	y = 0;
	while (y < map->dims.y)
	{
		map->objs[y] = ft_calloc(map->dims.x, sizeof(t_object *));
		if (map->objs[y] == NULL)
			return (map_destroy(&map), NULL);
		y++;
	}
	map->none = object_init(OBJ_NONE);
	map->none->above = map->none;
	map->none->below = map->none;
	return (map);
}

/* t_object **map_index(t_map *map, t_upoint p)
 * Return the address of the pointer at point p in map.
 * Return the address of NOWHERE if p is out of bounds.
 */
t_object	**map_index(t_map *map, t_upoint p)
{
	if (p.y >= map->dims.y || p.x >= map->dims.x)
		return (&map->none);
	return (&map->objs[p.y][p.x]);
}

void	map_destroy(t_map **map)
{
	t_upoint	p;
	t_object	**slot;

	if (*map == NULL)
		return ;
	p.y = 0;
	while (p.y < (*map)->dims.y)
	{
		p.x = 0;
		while (p.x < (*map)->dims.x)
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
