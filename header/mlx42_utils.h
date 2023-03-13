/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 16:37:00 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 16:26:58 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_UTILS_H
# define MLX42_UTILS_H

# include "MLX42/MLX42.h"
# include <stdint.h>

typedef enum {
	R = 0,
	G,
	B,
	A,
	BPP,
}	t_channel;

void	texture_area_copy_to_image(mlx_image_t *img, mlx_texture_t *txr,
		uint32_t dstxy[2], uint32_t srcxy[2]);
uint8_t	*pixel_get(uint8_t *pixels, uint32_t wh[2], uint32_t x, uint32_t y);
void	pixel_overlay(uint8_t *pixel, uint8_t *overlay);

#endif
