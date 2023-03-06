/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_tick_player.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:04:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 16:08:19 by dbasting      ########   odam.nl         */
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
	if (plyr->speed)
		plyr_tick_move(plyr, game);
	plyr_change_sprites(plyr, game);
	plyr_check_collisions(plyr, game);
}

static void	plyr_tick_move(t_object *plyr, t_game *game)
{
	object_move_sprite(plyr);
	if (object_align_grid(plyr, game))
	{
		plyr->speed = 0;
		game->lock_input = false;
		if (!hook_keys_move(game))
		{
			sprite_change(plyr, game->sprites[SPR_PLYR_IDLE], game);
			plyr->sprite->frame = 0;
		}
	}
	view_shift(
		instance_to_point(plyr->sprite->image->instances[plyr->instance_id]),
		game);
}

static void	plyr_change_sprites(t_object *plyr, t_game *game)
{
	if (game->ticks % 48 == 24)
		plyr->sprite->animator = sprite_animate;
	else if (sprite_animation_is_done(plyr->sprite))
	{
		plyr->sprite->frame = 0;
		plyr->sprite->animator = sprite_animate_pass;
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
