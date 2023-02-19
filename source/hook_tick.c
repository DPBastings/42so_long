/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hook_tick.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 16:50:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <float.h>

static void	sprites_animate(t_game *game);

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
	game->ticks++;
	sprites_animate(game);
}

static void	sprites_animate(t_game *game)
{
	unsigned int	id;

	if (game->ticks % TICKS_PER_ANIM_FG)
		return ;
	id = SPR_COLL_0;
	while (id < SPR_COLL_MAX)
	{
		sprite_animate_coll(game->sprites[id], game);
		game->sprites[id]->frame++;
		id++;
	}
}
