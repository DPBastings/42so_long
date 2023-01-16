/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/16 18:31:44 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>
#include "libftprintf.h"
#include "draw.h"

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*root;
	void		*wall;
	t_plane	 	dims;
	//int			count;
	
	(void) argv;
	if (argc != 2)
	{
		ft_dprintf(2, "Usage: so_long [map].\n");
		return (0);
	}
	mlx = mlx_init();
	root = mlx_new_window(mlx, 1080, 720, "Zo lang, en dank voor alle vis.");
	wall = mlx_xpm_file_to_image(mlx, "./wall", &dims.w, &dims.h);
	ft_printf("%p\n", wall);
	//count = 0;	
	//while (count < 12)
	//{
		mlx_put_image_to_window(mlx, root, wall, 0, 0);
		//count++;
	//}
	mlx_loop(mlx);
}
