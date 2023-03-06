/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_move.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:00:55 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 16:35:20 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include <stdbool.h>
#include <stdint.h>

static const uint32_t	g_lookup_dir[N_DIRS][N_DIM] = {
{0, -1},
{1, 0},
{0, 1},
{-1, 0},
};

void	object_move(t_object *obj, t_dir dir, uint32_t speed)
{
	obj->dir = dir;
	obj->speed = speed;
}

void	object_move_sprite(t_object *obj)
{
	mlx_instance_t	*instance;

	instance = &obj->sprite->image->instances[obj->instance_id];
	instance->x += g_lookup_dir[obj->dir][X] * obj->speed;
	instance->y += g_lookup_dir[obj->dir][Y] * obj->speed;
}

void	object_place(t_object *obj, t_map *map, t_upoint p)
{
	t_object	**coordinate;

	*map_index(map, obj->position) = obj->obj_below;
	coordinate = map_index(map, p);
	obj->obj_below = *coordinate;
	*coordinate = obj;
	obj->position = p;
}

bool	object_align_grid(t_object *obj, t_game *game)
{
	mlx_instance_t	instance;
	t_upoint		p;

	instance = obj->sprite->image->instances[obj->instance_id];
	set_upoint(&p,
		view_xgrid(instance.x, game->view),
		view_ygrid(instance.y, game->view));
	if (p.x % GRID_W == 0 && p.y % GRID_H == 0)
	{
		set_upoint(&p, p.x / GRID_W, p.y / GRID_H);
		object_place(obj, game->map, p);
		return (true);
	}
	return (false);
}

t_upoint	upoint_get_adjacent(t_upoint p, t_dir dir)
{
	p.x += g_lookup_dir[dir][X];
	p.y += g_lookup_dir[dir][Y];
	return (p);
}
