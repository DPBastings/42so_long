/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_change.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:31:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 13:26:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>

static void	instance_update_position(t_object *obj, t_view view);

void	sprite_change(t_object *obj, t_sprite *new_spr, t_game *game)
{
	int32_t	new_id;

	if (obj->sprite)
		obj->sprite->image->instances[obj->instance_id].enabled = false;
	new_id = 0;
	while (new_id < new_spr->image->count)
	{
		if (new_spr->image->instances[new_id].enabled == false)
			break ;
		new_id++;
	}
	if (new_id == new_spr->image->count)
	{
		new_id = mlx_image_to_window(game->mlx, new_spr->image, 0, 0);
		if (new_id == -1)
			sl_error(SL_MEMFAIL);
	}
	new_spr->image->instances[new_id].enabled = true;
	obj->instance_id = new_id;
	obj->sprite = new_spr;
	instance_update_position(obj, game->view);
}

static void	instance_update_position(t_object *obj, t_view view)
{
	mlx_instance_t	*instance;

	instance = &obj->sprite->image->instances[obj->instance_id];
	instance->x = view_xview(obj->position.x * GRID_W, view);
	instance->y = view_yview(obj->position.y * GRID_H, view);
	mlx_set_instance_depth(instance, obj->z);
}
