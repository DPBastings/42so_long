/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx42_string.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:53:50 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 16:41:11 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_STRING_H
# define MLX_42_STRING_H

# include "MLX42/MLX42.h"
# include <stdint.h>

# define GLYPH_W		10
# define GLYPH_H		20
# define GLYPHS_PER_ROW	32

# define COLOUR			CLR_WHITE

void	string_to_image(char const *str, mlx_image_t *img, uint32_t xy[2],
		mlx_texture_t *font);
void	char_to_image(char const chr, mlx_image_t *img, uint32_t xy[2],
		mlx_texture_t *font);
uint8_t	*find_char(char const chr, mlx_texture_t *font);

#endif
