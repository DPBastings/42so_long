/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 17:20:53 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 11:54:37 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <float.h>
#include "libft.h"
#include "MLX42/MLX42.h"

static void	create_vortex(t_game *game);

void	object_collect(t_game *game, t_object **obj)
{
	object_remove(*obj, game->map);
	object_destroy(obj);
	game->score++;
	ft_printf("> Score:  %u out of %u.\n", game->score, game->score_max);
}

void	game_win(t_game *game)
{
	ft_printf("You've made it!\n");
	game_exit(game);
}

void	game_lose(t_game *game)
{
	ft_printf("Ow!\n");
	game_exit(game);
}

void	game_exit(t_game *game)
{
	game->lock_input = 1;
	mlx_close_window(game->mlx);
}
