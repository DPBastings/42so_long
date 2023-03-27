/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:55:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/27 12:43:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_image.h"
#include "sl_error.h"

#include "MLX42/MLX42.h"
#include <stddef.h>
#include <stdint.h>

mlx_image_t	*image_init(mlx_t *mlx, uint32_t width, uint32_t height)
{
	mlx_image_t	*img;

	if (mlx == NULL || width == 0 || height == 0)
		return (NULL);
	img = mlx_new_image(mlx, width, height);
	if (img == NULL)
		sl_error(SL_MEMFAIL);
	return (img);
}

mlx_image_t	*image_from_texture_init(mlx_t *mlx, mlx_texture_t *txr)
{
	mlx_image_t	*img;

	if (mlx == NULL || txr == NULL)
		return (NULL);
	img = mlx_texture_to_image(mlx, txr);
	if (img == NULL)
		sl_error(SL_MEMFAIL);
	return (img);
}

int32_t	image_render(mlx_t *mlx, mlx_image_t *img, int32_t x, int32_t y)
{
	int32_t	id;

	id = mlx_image_to_window(mlx, img, x, y);
	if (id == -1)
		sl_error(SL_MEMFAIL);
	return (id);
}
