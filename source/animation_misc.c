/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation_misc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:07:25 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 13:21:04 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>

void	sprite_animate_coll(t_sprite *spr, void *param)
{
	t_game		*game;

	game = param;
	sprite_hueshift(spr, game->textures[TXR_GRADIENT]);
	spr->frame++;
}

void	sprite_animate_vortex(t_sprite *spr, void *param)
{
	t_game	*game;

	game = param;
	sprite_animate(spr, game);
	sprite_hueshift(spr, game->textures[TXR_GRADIENT]);
}
