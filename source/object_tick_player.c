/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_tick_player.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:04:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 16:20:20 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>

static void	plyr_change_sprites(t_object *plyr, t_game *game);
static void	plyr_check_collisions(t_object *plyr, t_game *game);
static void	plyr_tick_move(t_object *plyr, t_game *game);

void	object_tick_player(t_object *plyr, void *param)
{
	t_game		*game;

	object_tick_default(plyr, param);
	game = param;
	plyr_tick_move(plyr, game);
	plyr_change_sprites(plyr, game);
	plyr_check_collisions(plyr, game);
}

static void	plyr_tick_move(t_object *plyr, t_game *game)
{
	object_move_sprite(plyr);
	if (object_align_grid(plyr, game->map))
		plyr->speed = 0;
}

static void	plyr_change_sprites(t_object *plyr, t_game *game)
{
	if (plyr->speed == 0 && sprite_animation_is_done(plyr->sprite))
	{
		game->lock_input = false;
		sprite_change(plyr, game->sprites[SPR_PLYR], game);
		plyr->sprite->frame = 0;
	}
	if (plyr->sprite == game->sprites[SPR_PLYR] && game->ticks % 48 == 0)
	{
		sprite_change(plyr, game->sprites[SPR_PLYR_IDLE], game);
		plyr->sprite->frame = 0;
	}
}	

static void	plyr_check_collisions(t_object *plyr, t_game *game)
{
	t_object	*other;

	other = plyr->obj_below;
	if (other)
	{
		if (other->type == OBJ_COLL)
		{
			plyr->obj_below = other->obj_below;
			object_collect(game, &other);
		}
		else if (other->type == OBJ_EXIT && game->score == game->score_max)
			game_exit(game);
	}
}
