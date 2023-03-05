/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:16 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:05:01 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/MLX42.h"

void	hook_set(t_game *game)
{
	mlx_close_hook(game->mlx, hook_close, game);
	mlx_loop_hook(game->mlx, hook_keys, game);
	//mlx_loop_hook(game->mlx, hook_tick, game);
}
