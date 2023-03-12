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

static const uint32_t	g_lookup_movekeys[N_DIRS] = {
	SL_KEY_UP,
	SL_KEY_RIGHT,
	SL_KEY_DOWN,
	SL_KEY_LEFT,
};

static void	hook_esc(t_game *game);

void	hook_keys(void *param)
{
	t_game	*game;

	game = param;
	if (!game->lock_input)
		hook_keys_move(game);
	hook_esc(game);
}

bool	hook_keys_move(t_game *game)
{
	uint32_t	dir;

	dir = 0;
	while (dir < N_DIRS)
	{	
		if (mlx_is_key_down(game->mlx, g_lookup_movekeys[dir]))
			return (player_move(game, dir));
		dir++;
	}
	return (false);
}

static void	hook_esc(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
