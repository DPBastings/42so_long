/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:07:58 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 13:34:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"

#include <float.h>
#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

void	pixels_set(uint8_t *pixels, size_t n, uint32_t value)
{
	uint32_t	*px;

	px = (uint32_t *)pixels;
	while (n)
		px[--n] = value;
}

void	pixels_set_channel(uint8_t *pixels, size_t n, t_channel channel,
		uint8_t value)
{
	while (n)
		pixels[--n * BPP + channel] = value;
}

// The pesky Norm precludes more than four parameters. I've decided to drop `wh`
// for the purposes of this project (since it'll always be a 48x48 area that's
// being copied.
void	texture_area_copy_to_image(mlx_image_t *img, mlx_texture_t *txr,
		uint32_t dstxy[2], uint32_t srcxy[2])
{
	uint8_t		*dst;
	uint8_t		*src;
	uint32_t	wh[2];
	uint32_t	y;

	wh[0] = 48;
	wh[1] = 48;
	y = 0;
	while (y < wh[1])
	{
		dst = &img->pixels[((dstxy[1] + y) * img->width + dstxy[0]) * BPP];
		src = &txr->pixels[((srcxy[1] + y) * txr->width + srcxy[0]) * BPP];
		ft_memmove(dst, src, wh[0] * BPP);
		y++;
	}
}

uint8_t	*pixel_get(uint8_t *pixels, uint32_t const wh[2],
		uint32_t x, uint32_t y)
{
	if (pixels == NULL || x >= wh[0] || y >= wh[1])
		return (NULL);
	return (&pixels[(y * wh[0] + x) * BPP]);
}

void	pixel_overlay(uint8_t *pixel, uint8_t *overlay)
{
	double	factor;
	uint8_t	max;
	uint8_t	min;
	size_t	i;

	if (pixel == NULL || overlay == NULL)
		return ;
	if (pixel[R] == pixel[G] && pixel[G] == pixel[B])
		return ;
	max = ft_uintmax(3, pixel[R], pixel[G], pixel[B]);
	min = ft_uintmin(3, pixel[R], pixel[G], pixel[B]);
	factor = (double)(max - min) / UCHAR_MAX;
	i = R;
	while (i < A)
	{
		pixel[i] = (uint8_t)(factor * overlay[i]);
		i++;
	}
}
