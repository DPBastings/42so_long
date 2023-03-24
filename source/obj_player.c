/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:04:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 13:35:37 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_view.h"

#include <stdbool.h>

#define IDLE_ANIM_INTV	60

static void	player_change_sprites(t_object *player, t_game *game);
static void	player_collisions(t_object *player, t_game *game);
static void	player_keys(t_object *player, t_game *game);
static void	player_tick_move(t_object *player, t_game *game);

void	tick_player(t_object *player, t_game *game)
{
	tick_default(player, game);
	if (player->speed)
		player_tick_move(player, game);
	if (!game->lock_input)
		player_keys(player, game);
	player_change_sprites(player, game);
	player_collisions(player, game);
}

static void	player_change_sprites(t_object *player, t_game *game)
{
	if (player->sprite == game->sprites[SPR_PLYR_IDLE])
	{
		if (game->ticks % IDLE_ANIM_INTV == IDLE_ANIM_INTV - 1)
			player->sprite->animator = sprite_animate;
		else if (sprite_animation_is_done(player->sprite))
		{
			player->sprite->frame = 0;
			player->sprite->animator = sprite_animate_pass;
		}
	}
}

static void	player_collisions(t_object *player, t_game *game)
{
	t_object	*other;

	other = player->below;
	while (other)
	{
		if (other->type == OBJ_COLL)
		{
			object_collect(game, &other);
			image_hueshift(player->sprite->image, game->textures[TXR_GRADIENT],
				game->seed / game->ticks);
			textures_plyr_hueshift(game->textures, game->seed / game->ticks);
			continue ;
		}
		else if (obj_is_harmful(other))
			game_lose(game);
		else if (other->type == OBJ_EXIT && game->score == game->score_max)
			game_win(game);
		other = other->below;
	}
}

static void	player_keys(t_object *player, t_game *game)
{
	t_dir			dir;
	keys_t const	lut_movement_keys[N_DIRS / 2] = {
		SL_KEY_UP, SL_KEY_RIGHT, SL_KEY_DOWN, SL_KEY_LEFT};

	dir = 0;
	while (dir < N_DIRS / 2)
	{
		if (mlx_is_key_down(game->mlx, lut_movement_keys[dir]))
		{
			player_move(game, dir * 2);
			return ;
		}
		dir++;
	}
}

static void	player_tick_move(t_object *player, t_game *game)
{
	t_point	a;

	if (tick_move(player, game))
	{
		player->speed = 0;
		game->lock_input = false;
		sprite_change(player, game->sprites[SPR_PLYR_IDLE], game);
		player->sprite->frame = 0;
	}
	a = instance_to_point(
			player->sprite->image->instances[player->instance_id]);
	set_point(&a, a.x + GRID_W / 2, a.y + GRID_H / 2);
	view_shift(&game->view, a, game->map);
}
