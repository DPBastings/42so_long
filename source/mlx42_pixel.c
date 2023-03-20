/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_pixel.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:07:58 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 12:36:58 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx42_utils.h"
#include "MLX42/MLX42.h"

#include <float.h>
#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

//This does not take into account endianness.
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
