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
#include "MLX42/MLX42.h"

void	object_collect(t_game *game, t_object **obj)
{
	object_destroy(obj);
	game->score++;
	ft_printf("> Score:  %u out of %u.\n",
		game->score, game->score_max);
	if (game->score == game->score_max)
	{
		game->sprites[SPR_EXIT]->animator = sprite_animate;
		game->map->exit->sprite->frame_max = 16;
	}
}

void	game_exit(t_game *game)
{
	game->lock_input = 1;
	ft_printf("You've made it!\n");
	mlx_close_window(game->mlx);
}
