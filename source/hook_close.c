/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_close.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 15:21:31 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 17:00:49 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/MLX42.h"

void	hook_close(void *param)
{
	t_game	*game;

	game = param;
	mlx_close_window(game->mlx);
}
