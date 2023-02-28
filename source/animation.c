/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:07:09 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:07:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "mlx42_utils.h"
#include <math.h>
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
	uint8_t	*src;
	uint8_t	*dst;
	t_point	p;

	(void) param;
	p.x = spr->frame * GRID_W % spr->texture->width;
	p.y = 0;
	while (p.y < spr->image->height)
	{
		src = &spr->texture->pixels[(p.y * spr->texture->width + p.x) * BPP];
		dst = &spr->image->pixels[p.y * GRID_H * BPP];
		ft_memmove(dst, src, GRID_W * BPP);
		p.y++;
	}
	spr->frame++;
}

bool	sprite_animation_is_done(t_sprite *spr)
{
	if (spr == NULL)
		return (false);
	return (spr->frame >= spr->frame_max);
}
