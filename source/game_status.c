/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 17:20:53 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/20 13:08:21 by dbasting      ########   odam.nl         */
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
		game->map->exit->passable = true;
}

void	game_exit(t_game *game)
{
	game->lock_input = 1;
	ft_printf("You've made it!\n");
	mlx_close_window(game->mlx);
}
