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
#include "map.h"

void	map_view(t_map map)
{
	t_map	slice;
	
	slice = map;
	while (*slice)
		ft_printf("%s", *(slice++));
}

int	main(void)
{
	t_map	map;

	map = map_read("./assets/maps/map0");
	map_view(map);
	return (0);
}

/*int	main(int argc, char **argv)
{
	void	*mlx;:q
	void	*root;
	void	*wall;
	t_plane	dims;
	size_t	count;

	(void) argv;
	if (argc != 2)
	{
		ft_dprintf(2, "Usage: so_long [map].\n");
		return (0);
	}
	mlx = mlx_init();
	root = mlx_new_window(mlx, 1080, 720, "Zo lang, en dank voor alle vis.");
	dims.w = GRID_SIZE;
	dims.h = GRID_SIZE;
	wall = mlx_xpm_file_to_image(mlx, "./assets/textures/stone_wall.xpm", &dims.w, &dims.h);
	count = 0;
	while (count < 12)
	{
		mlx_put_image_to_window(mlx, root, wall, count * GRID_SIZE, 0);
		count++;
	}
	mlx_loop(mlx);
}*/
