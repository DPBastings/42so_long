/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 12:21:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/16 18:19:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

typedef unsigned int	t_colour;

# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define GREY	0x00888888
# define DIM_LILAC	0x0067477D
# define BRIGHT_LILAC 0x00A656DB

typedef struct	s_plane {
	int	w;
	int	h;
}	t_plane;

typedef struct	s_canvas {
	void	*image;
	char	*address;
	int		bpp;
	int		len;
	int		endian;
}	t_canvas;

void		draw_point(t_canvas *canvas, int x, int y, t_colour colour);
void		draw_plane(t_canvas *canvas, int x, int y, t_plane dims, t_colour colour);
t_canvas	*canvas_new(void *mlx_ptr, int x, int y);
void		canvas_destroy(void *mlx_ptr, t_canvas *canvas);
t_canvas	*load_texture(void *mlx_ptr, char const *file, t_plane dims);

#endif
