/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_enemy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 10:39:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 11:29:27 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>

static bool	tick_enemy_base(t_object *enmy, void *param);

void	tick_enemy_easy(t_object *enmy, void *param)
{
	t_game		*game;
	t_spr_id	nspr;

	if (!tick_enemy_base(enmy, param))
		return ;
	game = param;
	if (!enemy_move(enmy, game))
	{
		enmy->dir = dir_invert(enmy->dir);
		nspr = SPR_ENMY_MOVE_UP + enmy->dir / 2;
		sprite_change(enmy, game->sprites[nspr], game);
	}
}

void	tick_enemy_hard(t_object *enmy, void *param)
{
	t_game	*game;

	if (!tick_enemy_base(enmy, param))
		return ;
	game = param;
	if (!enemy_move(enmy, game))
	{
		enmy->dir = (enmy->dir + 2) % N_DIRS;
		sprite_change(enmy, game->sprites[SPR_ENMY_MOVE_UP + enmy->dir], game);
	}
}

static bool	tick_enemy_base(t_object *enmy, void *param)
{
	t_game		*game;
	t_object	**other;

	tick_default(enmy, param);
	game = param;
	return (tick_move(enmy, game));
}
