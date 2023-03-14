/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 15:42:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 12:19:00 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>
#include <stdint.h>

static void	create_vortex(t_object *exit, t_game *game);

void	tick_exit(t_object *exit, t_game *game)
{
	if (exit->sprite->animator == sprite_animate
		&& sprite_animation_is_done(exit->sprite))
		exit->sprite->animator = sprite_animate_pass;
	else if (game->hud->bar->filled >= 1 && !exit->below)
		exit_open(exit, game);
}

void	exit_open(t_object *exit, t_game *game)
{
	create_vortex(exit, game);
	game->sprites[SPR_EXIT]->animator = sprite_animate;
	game->map->exit->sprite->frame_max = 16;
}

static void	create_vortex(t_object *exit, t_game *game)
{
	t_object	*anim;

	anim = ft_calloc(1, sizeof(t_object));
	if (anim == NULL)
		sl_error(SL_MEMFAIL);
	anim->type = OBJ_ANIM;
	anim->position = exit->position;
	anim->z = Z_BG1;
	sprite_change(anim, game->sprites[SPR_VORTEX], game);
	anim->sprite->frame_max = -1;
	anim->sprite->animator = sprite_animate_vortex;
	object_insert_below(anim, exit);
}
