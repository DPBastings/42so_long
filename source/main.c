/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/01/23 18:04:38 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "draw.h"
#include "libftprintf.h"
#include "map.h"
#include <mlx.h>
#include <stdlib.h>

#include "sl_test.h"

void	sl_error(char const *message)
{
	ft_dprintf(2, "Error:\n%s\n", message);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	//void	*mlx;
	//void	*root;
	t_map	*map;

	if (argc != 2)
		sl_error("Usage: so_long [map].");
	//mlx = mlx_init();
	//root = mlx_new_window(mlx, 1152, 864, "The Bach Game");
	map = map_read(argv[1]);
	if (map == NULL)
		sl_error("Error reading map from file.");
	map_destroy(&map);
	/*if (!map_check(map))
	{
		map_destroy(&map);
		sl_error("That map does not constitute a valid level.");
	}
	map_view(map);*/
	//map_draw(mlx, map);
	//mlx_loop(mlx);
	return (0);
}

/*int	main(int argc, char **argv)
{
	void	*mlx;
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
