/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_string.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:53:50 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 17:11:19 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_STRING_H
# define MLX42_STRING_H

# include "MLX42/MLX42.h"
# include <stdint.h>

# define CHAR_W			10
# define CHAR_H			20
# define CHARS_PER_ROW	32

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

void	string_to_image(char const *str, mlx_image_t *img, uint32_t xy[2],
		t_style *style);
void	char_to_image(char const chr, mlx_image_t *img, uint32_t xy[2],
		t_style *style);
uint8_t	*find_char(char const chr, mlx_texture_t *font);

#endif
