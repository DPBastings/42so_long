/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_hueshift.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:32:26 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/24 13:34:48 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include "geometry.h"

void	sprite_overlay_gradient(t_sprite *sprite, mlx_texture_t *gradient)
{
	t_upoint	p;
	t_plane		a;

	if (sprite == NULL || gradient == NULL)
		return ;
	set_plane(&a, GRID_W, GRID_H);
	p.y = 0;
	while (p.y < sprite->image->height)
	{
		p.x = 0;
		while (p.x < sprite->image->width)
		{
			pixel_overlay(
				pixel_get(sprite->image->pixels, (uint32_t *)&a, p.x, p.y),
				gradient_read(gradient, sprite->frame));
			p.x++;
		}
		p.y++;
	}
}

void	sprite_overlay_gradient_line(t_sprite *sprite, mlx_texture_t *gradient)
{
	t_upoint	p;
	t_plane		a;

	if (sprite == NULL || gradient == NULL)
		return ;
	set_plane(&a, GRID_W, GRID_H);
	p.y = 0;
	while (p.y < sprite->image->height)
	{
		p.x = 0;
		while (p.x < sprite->image->width)
		{
			pixel_overlay(
				pixel_get(sprite->image->pixels, (uint32_t *)&a, p.x, p.y),
				gradient_read(gradient, p.x + sprite->frame));
			p.x++;
		}
		p.y++;
	}
}

uint8_t	*gradient_read(mlx_texture_t *gradient, uint32_t i)
{
	if (gradient == NULL)
		return (NULL);
	i %= gradient->width - 1;
	return (&gradient->pixels[i * BPP]);
}
