/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation_coll.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:07:25 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 16:06:19 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>

void	sprite_animate_coll(t_sprite *spr, void *param)
{
	t_game		*game;

	game = param;
	sprite_overlay_gradient(spr, game->textures[TXR_GRADIENT]);
	spr->frame++;
}

void	sprite_animate_vortex(t_sprite *spr, void *param)
{
	t_game	*game;

	game = param;
	sprite_animate(spr, game);
	sprite_overlay_gradient(spr, game->textures[TXR_GRADIENT]);
}
