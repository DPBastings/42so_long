/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_tick.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 11:28:31 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <float.h>

void	hook_tick(void *param)
{
	static double	time_prev;
	double			time_now;
	t_game			*game;

	game = param;
	time_now = mlx_get_time();
	if (time_now - time_prev < SEC_PER_TICK)
		return ;
	time_prev = time_now;
	objects_tick(game);
	sprites_animate(game);
	game->ticks++;
}
