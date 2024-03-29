/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_hueshift.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:32:26 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 13:20:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include "point.h"

void	sprite_hueshift(t_sprite *sprite, mlx_texture_t *gradient)
{
	if (sprite == NULL || gradient == NULL)
		return ;
	image_hueshift(sprite->image, gradient, sprite->frame);
}

void	image_hueshift(mlx_image_t *img, mlx_texture_t *gradient,
		uint32_t frame)
{
	t_upoint		px;
	uint32_t const	wh[2] = {img->width, img->height};

	px.y = 0;
	while (px.y < img->height)
	{
		px.x = 0;
		while (px.x < img->width)
		{
			pixel_overlay(
				pixel_get(img->pixels, wh, px.x, px.y),
				gradient_read(gradient, frame));
			px.x++;
		}
		px.y++;
	}
}

void	texture_hueshift(mlx_texture_t *txr, mlx_texture_t *gradient,
		uint32_t frame)
{
	t_upoint		px;
	uint32_t const	wh[2] = {txr->width, txr->height};

	px.y = 0;
	while (px.y < txr->height)
	{
		px.x = 0;
		while (px.x < txr->width)
		{
			pixel_overlay(
				pixel_get(txr->pixels, wh, px.x, px.y),
				gradient_read(gradient, frame));
			px.x++;
		}
		px.y++;
	}
}

void	bar_hueshift(mlx_image_t *bar, mlx_texture_t *gradient,
		uint32_t i)
{
	t_upoint		px;
	uint32_t const	wh[2] = {bar->width, bar->height};

	i = gradient->width - i % gradient->width;
	px.y = 0;
	while (px.y < bar->height)
	{
		px.x = 0;
		while (px.x < bar->width)
		{
			pixel_overlay(
				pixel_get(bar->pixels, wh, px.x, px.y),
				gradient_read(gradient, i + px.x / 4 + px.y / 2));
			px.x++;
		}
		px.y++;
	}
}

uint8_t	*gradient_read(mlx_texture_t *gradient, uint32_t i)
{
	if (gradient == NULL)
		return (NULL);
	i %= gradient->width - 1;
	return (&gradient->pixels[i * BPP]);
}
