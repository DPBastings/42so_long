/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 16:37:00 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 14:46:13 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_UTILS_H
# define MLX42_UTILS_H

# include "MLX42/MLX42.h"
# include <stddef.h>
# include <stdint.h>

# define CLR_WHITE		0xFFFFFFFF
# define CLR_GREY		0x0F0F0FFF
# define CLR_BLACK		0x000000FF
# define CLR_RED		0xFF0000FF
# define CLR_ORANGE		0xFF8800FF
# define CLR_YELLOW		0xFFFF00FF
# define CLR_GREEN		0x00FF00FF
# define CLR_CYAN		0x00FFFFFF
# define CLR_BLUE		0x0000FFFF
# define CLR_MAGENTA	0xFF00FFFF

# define CHAR_W			10
# define CHAR_H			20
# define CHARS_PER_ROW	32

typedef enum e_channel {
	R = 0,
	G,
	B,
	A,
	BPP,
}	t_channel;

typedef struct s_font {
	mlx_texture_t	*txr;
	uint32_t		char_w;
	uint32_t		char_h;
	uint32_t		chars_per_row;
}	t_font;

typedef struct s_style {
	mlx_texture_t	*font;
	uint32_t		size;
	uint32_t		colour;
}	t_style;

/*Image building functions*/
void	image_tile(mlx_image_t *img, mlx_texture_t *txr, uint32_t grid[2]);
void	texture_copy_to_image(mlx_image_t *img, mlx_texture_t *txr,
			uint32_t dstxy[2]);
void	texture_area_copy_to_image(mlx_image_t *img, mlx_texture_t *txr,
			uint32_t dstxy[2], uint32_t srcxy[2]);

/*Pixel manipulation functions*/
void	pixels_set(uint8_t *pixels, size_t n, uint32_t value);
void	pixels_set_channel(uint8_t *pixels, size_t n, t_channel channel,
			uint8_t value);
uint8_t	*pixel_get(uint8_t *pixels, uint32_t const wh[2],
			uint32_t x, uint32_t y);
void	pixel_overlay(uint8_t *pixel, uint8_t *overlay);

/*String functions*/
void	string_to_image(char const *str, mlx_image_t *img, uint32_t xy[2],
			t_style *style);
void	char_to_image(char const chr, mlx_image_t *img, uint32_t xy[2],
			t_style *style);
uint8_t	*find_char(char const chr, mlx_texture_t *font);

#endif
