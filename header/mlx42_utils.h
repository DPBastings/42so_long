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
# include <stddef.h>
# include <stdint.h>

# define CLR_WHITE		0xFFFFFFFF
# define CLR_GREY		0xFF0F0F0F
# define CLR_BLACK		0xFF000000
# define CLR_RED		0xFF0000FF
# define CLR_ORANGE		0xFF000FFF
# define CLR_YELLOW		0xFF00FFFF
# define CLR_GREEN		0xFF00FF00
# define CLR_CYAN		0xFFFFFF00
# define CLR_BLUE		0xFFFF0000
# define CLR_MAGENTA	0xFFFF00FF

typedef enum {
	R = 0,
	G,
	B,
	A,
	BPP,
}	t_channel;

void	pixels_set(uint8_t *pixels, size_t n, uint8_t const value[BPP]);
void	pixels_set_channel(uint8_t *pixels, size_t n, t_channel channel, uint8_t value);
void	texture_area_copy_to_image(mlx_image_t *img, mlx_texture_t *txr,
		uint32_t dstxy[2], uint32_t srcxy[2]);
uint8_t	*pixel_get(uint8_t *pixels, uint32_t const wh[2], uint32_t x, uint32_t y);
void	pixel_overlay(uint8_t *pixel, uint8_t *overlay);

#endif
