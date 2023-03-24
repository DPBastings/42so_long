/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:07:09 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 12:57:46 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "mlx42_utils.h"
#include <stdbool.h>

void	sprites_animate(t_game *game)
{
	t_spr_id	id;

	id = 1;
	while (id < N_SPRITES)
	{
		game->sprites[id]->animator(game->sprites[id], game);
		id++;
	}
}

void	sprite_animate_pass(t_sprite *spr, void *param)
{
	(void) spr;
	(void) param;
}

void	sprite_animate(t_sprite *spr, void *param)
{
	uint32_t const	dstxy[2] = {0, 0};
	uint32_t		srcxy[2];

	(void) param;
	srcxy[0] = spr->frame * GRID_W % spr->texture->width;
	srcxy[1] = 0;
	texture_area_copy_to_image(spr->image, spr->texture, dstxy, srcxy);
	spr->frame++;
}

bool	sprite_animation_is_done(t_sprite *spr)
{
	if (spr == NULL)
		return (false);
	return (spr->frame >= spr->frame_max);
}
