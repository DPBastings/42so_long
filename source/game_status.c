/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 17:20:53 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 11:43:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"
#include "MLX42/MLX42.h"

static void	create_vortex(t_game *game);

void	object_collect(t_game *game, t_object **obj)
{
	object_destroy(obj);
	game->score++;
	ft_printf("> Score:  %u out of %u.\n",
		game->score, game->score_max);
	if (game->score == game->score_max)
	{
		create_vortex(game);
		game->sprites[SPR_EXIT]->animator = sprite_animate;
		game->map->exit->sprite->frame_max = 16;
	}
}

static void	create_vortex(t_game *game)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (obj == NULL)
		sl_error(SL_MEMFAIL);
	obj->type = OBJ_ANIM;
	obj->position = game->map->exit->position;
	obj->z = game->map->exit->z + 1;
	sprite_change(obj, game->sprites[SPR_VORTEX], game);
	obj->sprite->frame_max = -1;
	obj->sprite->animator = sprite_animate_vortex;
	mlx_set_instance_depth(&obj->sprite->image->instances[obj->instance_id],
		obj->z);
	game->map->exit->obj_below = obj;
}

void	game_exit(t_game *game)
{
	game->lock_input = 1;
	ft_printf("You've made it!\n");
	mlx_close_window(game->mlx);
}
