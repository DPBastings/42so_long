/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_search.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:45 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 16:50:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"
#include <stdlib.h>
#include <limits.h>

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
