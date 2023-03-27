/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_string.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:54:39 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/27 14:11:32 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx42_utils.h"
#include <stddef.h>

void	string_to_image(char const *str, mlx_image_t *img, uint32_t xy[2],
		t_style *style)
{
	uint32_t	origin[2];

	origin[0] = xy[0];
	origin[1] = xy[1];
	while (*str)
	{
		if (*str == '\n')
		{
			xy[1] += CHAR_H * 1.5 * style->size;
			xy[0] = origin[0];
		}
		else
		{
			char_to_image(*str, img, xy, style);
			xy[0] += CHAR_W * style->size;
		}
		str++;
	}
}

void	char_to_image(char const chr, mlx_image_t *img, uint32_t xy[2],
		t_style *style)
{
	uint32_t		*src;
	uint32_t		i[2];

	if (img == NULL || style == NULL)
		return ;
	i[1] = 0;
	src = (uint32_t *)find_char(chr, style->font);
	while (i[1] < CHAR_H * style->size)
	{
		i[0] = 0;
		while (i[0] < CHAR_W * style->size)
		{
			if (src[i[1] / style->size * style->font->width
					+ i[0] / style->size] == CLR_WHITE)
				mlx_put_pixel(img, xy[0] + i[0], xy[1] + i[1], style->colour);
			else
				mlx_put_pixel(img, xy[0] + i[0], xy[1] + i[1], 0x0);
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
	xy[0] = chr % CHARS_PER_ROW * CHAR_W;
	xy[1] = chr / CHARS_PER_ROW * CHAR_H;
	return (pixel_get(font->pixels, dims, xy[0], xy[1]));
}
