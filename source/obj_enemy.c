/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_enemy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 10:39:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 16:04:33 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>

static void	enemy_collisions(t_object *enemy, t_game *game);

void	tick_enemy(t_object *enemy, t_game *game)
{
	t_spr_id	nspr;

	tick_default(enemy, game);
	if (!tick_move(enemy, game))
		return ;
	if (!enemy_move(enemy, game))
	{
		enemy->dir = dir_invert(enemy->dir);
		nspr = SPR_ENMY_MOVE_UP + enemy->dir / 2;
		sprite_change(enemy, game->sprites[nspr], game);
	}
	enemy_collisions(enemy, game);
}

static void	enemy_collisions(t_object *enemy, t_game *game)
{
	t_object	*other;

	other = enemy->below;
	while (other)
	{
		if (other->type == OBJ_PLYR)
			game_lose(game);
		other = other->below;
	}
}
