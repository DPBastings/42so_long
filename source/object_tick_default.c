/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_tick_default.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:02:32 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:22:22 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"

static const uint32_t	g_lookup_dir[N_DIRS * N_DIM] = {
	0, -1,
	1, 0,
	0, 1,
	-1, 0,
};

void	object_tick_default(t_object *obj, void *param)
{
	t_game			*game;
	mlx_instance_t	*instance;

	obj->ticked = true;
	game = param;
	if (obj->moving > 0)
	{
		instance = &obj->sprite->image->instances[obj->instance_id];
		instance->x += g_lookup_dir[obj->facing * N_DIM + X]
			* (GRID_W / MOVEMENT_SPEED);
		instance->y += g_lookup_dir[obj->facing * N_DIM + Y]
			* (GRID_H / MOVEMENT_SPEED);
		if (instance->x % GRID_W == 0 && instance->y % GRID_H == 0)
		{
			object_place(obj, game->map,
				point_get_adjacent(obj->position, obj->facing));
			obj->moving--;
		}
	}
}
