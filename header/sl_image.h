/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_image.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 12:27:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 15:42:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_IMAGE_H
# define SL_IMAGE_H

# include "MLX42/MLX42.h"
# include <stdint.h>

mlx_image_t	*image_init(mlx_t *mlx, uint32_t width, uint32_t height);
mlx_image_t	*image_from_texture_init(mlx_t *mlx, mlx_texture_t *txr);
int32_t		image_render(mlx_t *mlx, mlx_image_t *img, int32_t x, int32_t y);

#endif
