/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_tile.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:27:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 17:03:02 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx42_utils.h"

static void	tile_copy(mlx_image_t *img, mlx_texture_t *txr,
				uint32_t dst[2], uint32_t grid[2]);

void	image_tile(mlx_image_t *img, mlx_texture_t *txr, uint32_t grid[2])
{
	uint32_t	i[2];

	i[1] = 0;
	while (i[1] < img->height)
	{
		i[0] = 0;
		while (i[0] < img->width)
		{
			tile_copy(img, txr, i, grid);
			i[0] += grid[0];
		}
		i[1] += grid[1];
	}
}

static void	tile_copy(mlx_image_t *img, mlx_texture_t *txr,
		uint32_t dst[2], uint32_t grid[2])
{
	uint32_t	src[2];

	if (dst[0] >= img->width - grid[0] && dst[0] != 0)
		src[0] = 2 * grid[0];
	else if (dst[0] > 0)
		src[0] = grid[0];
	else
		src[0] = 0;
	if (dst[1] >= img->height - grid[1] && dst[1] != 0)
		src[1] = 2 * grid[1];
	else if (dst[1] > 0)
		src[1] = grid[1];
	else
		src[1] = 0;
	texture_area_copy_to_image(img, txr, dst, src);
}

//lelijke beslisboom
