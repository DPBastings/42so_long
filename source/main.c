/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/09 16:20:50 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct	s_image {
	void	*image;
	char	*address;
	int		bits;
	int		len;
	int		endian;
}	t_image;



int	main(int argc, char **argv)
{
	void	*mlx;
	void	*root;
	t_image	canvas;
	int		*file;
	
	if (argc == 2)
	{
		mlx = mlx_init();
		root = mlx_new_window(mlx, 1080, 720, "Zo lang, en dank voor alle vis.");
		canvas.image = mlx_new_image(mlx, 720, 480);
		canvas.address = mlx_get_data_addr(canvas.image, 
											&canvas.bits, 
											&canvas.len, 
											&canvas.endian);
		mlx_loop(mlx);
	}
	
}
