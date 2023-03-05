/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_search.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:45 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 15:21:46 by dbasting      ########   odam.nl         */
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
		return (&NOWHERE);
	return (&map->objs[p.y][p.x]);
}

/* t_point *get_adjacent(t_point p, t_map *map)
 * Return an array of the points adjacent to `p` within `map`. This array
 * always comprises four elements in a set order.
 * If an adjacent point is out of bounds, the array will at that index contain 
 * NOWHERE (a t_point(x = UINT_MAX, y = UINT_MAX)).
 * Returns NULL if `p` is itself out of bounds.
 * The memory at the address returned by this function is dynamically allocated
 * and must therefore be passed to free() once no longer in use.
 */
/*t_point	*map_get_adjacent(t_map *map, t_point p)
{
	t_point	*adjacent;
	size_t	i;

	if (p.y >= map->dims.y || p.x >= map->dims.x)
		return (NULL);
	adjacent = malloc(N_DIRS * sizeof(t_point));
	if (adjacent == NULL)
		sl_error(SL_MEMFAIL);
	i = 0;
	set_point(&adjacent[i], UINT_MAX, UINT_MAX);
	if (p.y > 0)
		set_point(&adjacent[i], p.x, p.y - 1);
	set_point(&adjacent[++i], UINT_MAX, UINT_MAX);
	if (p.x < map->dims.x - 1)
		set_point(&adjacent[i], p.x + 1, p.y);
	set_point(&adjacent[++i], UINT_MAX, UINT_MAX);
	if (p.y < map->dims.y - 1)
		set_point(&adjacent[i], p.x, p.y + 1);
	set_point(&adjacent[++i], UINT_MAX, UINT_MAX);
	if (p.x > 0)
		set_point(&adjacent[i], p.x - 1, p.y);
	return (adjacent);
}*/
