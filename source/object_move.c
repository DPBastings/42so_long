/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:00:55 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:00:56 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdint.h>

static const uint32_t	g_lookup_dir[N_DIRS * N_DIM] = {
	0, -1,
	1, 0,
	0, 1,
	-1, 0,
};

void	object_move(t_object *obj, t_dir dir, int32_t dist)
{
	obj->moving = dist;
	obj->facing = dir;
}

void	object_place(t_object *obj, t_map *map, t_point p)
{
	t_object	**coordinate;

	*map_index(map, obj->position) = obj->obj_below;
	coordinate = map_index(map, p);
	obj->obj_below = *coordinate;
	*coordinate = obj;
	obj->position = p;
}

t_point	point_get_adjacent(t_point p, t_dir dir)
{
	p.x += g_lookup_dir[dir * N_DIM + X];
	p.y += g_lookup_dir[dir * N_DIM + Y];
	return (p);
}
