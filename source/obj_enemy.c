/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_enemy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 10:39:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 12:47:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>

static bool	tick_enemy_base(t_object *enemy, t_game *game);
static void	enemy_collisions(t_object *enemy, t_game *game);

void	tick_enemy_easy(t_object *enemy, t_game *game)
{
	t_spr_id	nspr;

	if (!tick_enemy_base(enemy, game))
		return ;
	if (!enemy_move(enemy, game))
	{
		enemy->dir = dir_invert(enemy->dir);
		nspr = SPR_ENMY_MOVE_UP + enemy->dir / 2;
		sprite_change(enemy, game->sprites[nspr], game);
	}
	enemy_collisions(enemy, game);
}

void	tick_enemy_hard(t_object *enemy, t_game *game)
{
	t_spr_id	nspr;

	if (!tick_enemy_base(enemy, game))
		return ;
	if (!enemy_move(enemy, game))
	{
		enemy->dir = (enemy->dir + 2) % N_DIRS;
		nspr = SPR_ENMY_MOVE_UP + enemy->dir / 2;
		sprite_change(enemy, game->sprites[nspr], game);
	}
}

static bool	tick_enemy_base(t_object *enemy, t_game *game)
{
	t_object	**other;

	tick_default(enemy, game);
	return (tick_move(enemy, game));
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
