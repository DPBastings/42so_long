/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:16 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 12:07:31 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"

#include "MLX42/MLX42.h"
#include <stdbool.h>

void	hook_set(t_game *game)
{
	bool	success;

	mlx_close_hook(game->mlx, hook_close, game);
	success = mlx_loop_hook(game->mlx, hook_keys, game);
	if (success == false)
		sl_error(SL_GENERIC);
	success = mlx_loop_hook(game->mlx, hook_tick, game);
	if (success == false)
		sl_error(SL_GENERIC);
}
