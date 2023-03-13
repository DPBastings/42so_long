/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_enemy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 10:39:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 11:39:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>

static bool	tick_enemy_base(t_object *enmy, void *param);

void	tick_enemy_easy(t_object *enmy, void *param)
{
	t_game	*game;

	game = param;
	if (!tick_enemy_base(enmy, param))
		return ;
	if (!enemy_move(enmy, game))
	{
		enmy->dir = dir_invert(enmy->dir);
		sprite_change(enmy, game->sprites[SPR_ENMY_MOVE_UP + enmy->dir], game);
	}
}

void	tick_enemy_hard(t_object *enmy, void *param)
{
	tick_enemy_base(enmy, param);
}

static bool	tick_enemy_base(t_object *enmy, void *param)
{
	t_game		*game;
	t_object	**other;

	tick_default(enmy, param);
	game = param;
	return (tick_move(enmy, game));
}
