/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_change.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:31:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/10 14:43:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>

static void	instance_update_position(t_object *obj, t_view view);

void	sprite_change(t_object *obj, t_sprite *newspr, t_game *game)
{
	int32_t	newinstance_id;

	if (obj->sprite)
		obj->sprite->image->instances[obj->instance_id].enabled = false;
	newinstance_id = 0;
	while (newinstance_id < newspr->image->count)
	{
		if (newspr->image->instances[newinstance_id].enabled == false)
			break ;
		newinstance_id++;
	}
	if (newinstance_id == newspr->image->count)
	{
		newinstance_id = mlx_image_to_window(game->mlx, newspr->image, 0, 0);
		if (newinstance_id == -1)
			sl_error(SL_MEMFAIL);
	}
	newspr->image->instances[newinstance_id].enabled = true;
	obj->instance_id = newinstance_id;
	obj->sprite = newspr;
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
