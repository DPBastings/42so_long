/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 11:20:47 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 12:58:18 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx42_utils.h"

#include "libft.h"
#include "MLX42/MLX42.h"

// The pesky Norm precludes more than four parameters. I've decided to drop `wh`
// for the purposes of this project (since it'll always be a 48x48 area that's
// being copied.
void	texture_area_copy_to_image(mlx_image_t *img, mlx_texture_t *txr,
		uint32_t const dstxy[2], uint32_t srcxy[2])
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

void	texture_copy_to_image(mlx_image_t *img, mlx_texture_t *txr,
		uint32_t const dstxy[2])
{
	uint8_t		*dst;
	uint8_t		*src;
	uint32_t	y;

	y = 0;
	while (y < txr->height && y < img->height)
	{
		dst = &img->pixels[((dstxy[1] + y) * img->width + dstxy[0]) * BPP];
		src = &txr->pixels[(y * txr->width * BPP)];
		ft_memmove(dst, src, txr->width * BPP);
		y++;
	}
}
