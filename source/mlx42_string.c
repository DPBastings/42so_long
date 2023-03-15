/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:54:39 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 15:01:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx42_string.h"
#include "libft.h"
#include "mlx42_utils.h"
#include <stddef.h>

#include <stdio.h>

#define TEXT_COLOUR	CLR_CYAN

void	string_to_image(char const *str, mlx_image_t *img, uint32_t xy[2],
		mlx_texture_t *font)
{
	uint32_t	x;

	x = xy[0];
	while (*str)
	{
		if (*str == '\n')
		{
			xy[1] += GLYPH_H;
			xy[0] = x;
		}
		else
		{
			char_to_image(*str, img, xy, font);
			xy[0] += GLYPH_W;
		}
		str++;
	}
}

void	char_to_image(char const chr, mlx_image_t *img, uint32_t xy[2],
		mlx_texture_t *font)
{
	uint32_t const	imgdims[2] = {img->width, img->height};
	uint32_t		*dst;
	uint32_t		*src;
	uint32_t		i[2];

	if (dst == NULL || src == NULL)
		return ;
	i[1] = 0;
	src = (uint32_t *)find_char(chr, font);
	while (i[1] < GLYPH_H)
	{
		i[0] = 0;
		while (i[0] < GLYPH_W)
		{
			dst = (uint32_t *)pixel_get(img->pixels, imgdims,
					xy[0] + i[0], xy[1] + i[1]);
			if (src[i[1] * GLYPHS_PER_ROW * GLYPH_W + i[0]] == CLR_WHITE)
				*dst = TEXT_COLOUR;
			i[0]++;
		}
		i[1]++;
	}
}

uint8_t	*find_char(char const chr, mlx_texture_t *font)
{
	uint32_t const	dims[2] = {font->width, font->height};
	uint32_t		xy[2];

	if (font == NULL)
		return (NULL);
	xy[0] = chr % GLYPHS_PER_ROW * GLYPH_W;
	xy[1] = chr / GLYPHS_PER_ROW * GLYPH_H;
	return (pixel_get(font->pixels, dims, xy[0], xy[1]));
}
