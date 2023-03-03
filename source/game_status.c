/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 17:20:53 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 15:52:55 by dbasting      ########   odam.nl         */
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
	t_object	*vortex;

	vortex = ft_calloc(1, sizeof(t_object));
	if (vortex == NULL)
		sl_error(SL_MEMFAIL);
	vortex->type = OBJ_ANIM;
	vortex->position = game->map->exit->position;
	vortex->z = game->map->exit->z + 1;
	sprite_change(vortex, game->sprites[SPR_VORTEX], game);
	vortex->sprite->frame_max = -1;
	vortex->sprite->animator = sprite_animate_vortex;
	mlx_set_instance_depth(&vortex->sprite->image->instances[vortex->instance_id],
			vortex->z);
	game->map->exit->obj_below = vortex;
}

void	game_exit(t_game *game)
{
	game->lock_input = 1;
	ft_printf("You've made it!\n");
	mlx_close_window(game->mlx);
}
