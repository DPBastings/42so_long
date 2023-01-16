/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/16 14:48:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libftprintf.h"
#include "draw.h"

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*root;
	t_canvas	*canvas;
	t_plane	 	dims;
	int			count;
	
	(void) argv;
	if (argc != 2)
	{
		ft_dprintf(2, "Usage: so_long [map].\n");
		return (0);
	}
	mlx = mlx_init();
	root = mlx_new_window(mlx, 1080, 720, "Zo lang, en dank voor alle vis.");
	canvas = canvas_new(mlx, 720, 480);
	dims.w = 16;
	dims.h = 16;
	count = 0;
	while (count < 12)
	{
		draw_plane(canvas, 0 + count * dims.w, 0 + count * dims.w, dims, DIM_LILAC);
		count++;
	}
	mlx_put_image_to_window(mlx, root, canvas->image, 0, 0);
	mlx_loop(mlx);
}
