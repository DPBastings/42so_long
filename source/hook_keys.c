/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_keys.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/20 13:13:32 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>

static void	hook_keys_move(t_game *game);
static void	hook_esc(t_game *game);

void	hook_keys(void *param)
{
	t_game	*game;

	game = param;
	if (!game->lock_input)
		hook_keys_move(game);
	hook_esc(game);
}

static void	hook_keys_move(t_game *game)
{
	if (mlx_is_key_down(game->mlx, SL_KEY_UP))
		player_move(game, 0, -1);
	else if (mlx_is_key_down(game->mlx, SL_KEY_LEFT))
		player_move(game, -1, 0);
	else if (mlx_is_key_down(game->mlx, SL_KEY_DOWN))
		player_move(game, 0, 1);
	else if (mlx_is_key_down(game->mlx, SL_KEY_RIGHT))
		player_move(game, 1, 0);
}

static void	hook_esc(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
