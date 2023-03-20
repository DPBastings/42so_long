/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_keys.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 15:32:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>

static void	hook_esc(t_game *game);

void	hook_keys(void *param)
{
	t_game	*game;

	game = param;
	hook_esc(game);
}

static void	hook_esc(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
