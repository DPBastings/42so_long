/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:00:55 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 16:18:05 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>
#include <stdint.h>

static const uint32_t	g_lookup_dir[N_DIRS * N_DIM] = {
	0, -1,
	1, 0,
	0, 1,
	-1, 0,
};

void	object_move(t_object *obj, t_dir dir, uint16_t speed)
{
	obj->dir = dir;
	obj->speed = speed;
}

void	object_move_sprite(t_object *obj)
{
	mlx_instance_t	*instance;
	
	instance = &obj->sprite->image->instances[obj->instance_id];
	instance->x += g_lookup_dir[obj->dir * N_DIM + X] * obj->speed;
	instance->y += g_lookup_dir[obj->dir * N_DIM + Y] * obj->speed;
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

bool	object_align_grid(t_object *obj, t_map *map)
{
	mlx_instance_t	instance;
	t_point			p;

	instance = obj->sprite->image->instances[obj->instance_id];
	if (instance.x % GRID_W == 0 && instance.y % GRID_H == 0)
	{
		set_point(&p, instance.x / GRID_W, instance.y / GRID_H);
		object_place(obj, map, p);
		return (true);
	}
	return (false);
}

t_point	point_get_adjacent(t_point p, t_dir dir)
{
	p.x += g_lookup_dir[dir * N_DIM + X];
	p.y += g_lookup_dir[dir * N_DIM + Y];
	return (p);
}
