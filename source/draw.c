/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/16 14:50:59 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include <mlx.h>
#include <stdlib.h>

void	draw_plane(t_canvas *cvs, int x, int y, t_plane dims, t_colour colour)
{
	int		w;
	int		h;

	h = -1;
	while (h++ < dims.h)
	{
		w = -1;
		while (w++ < dims.w)
			draw_point(cvs, x + w, y + h, colour);
	}
}

void	draw_point(t_canvas *canvas, int x, int y, t_colour colour)
{
	char	*byte;

	byte = canvas->address + 
		(y * canvas->len + x * (canvas->bpp / 8));
	*(unsigned int *)byte = colour;
}
