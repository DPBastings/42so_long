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
#include "MLX42/MLX42.h"
#include "libftprintf.h"
#include "map.h"
#include <stdlib.h>

#include "sl_test.h"

void	sl_error(char const *message)
{
	ft_dprintf(2, "Error:\n%s\n", message);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	//mlx_t	*mlx;
	t_map	*map;

	if (argc != 2)
		sl_error("Usage: so_long [map].");
	//mlx = mlx_init(1258, 768, "The Bach Game", true);
	map = map_read(argv[1]);
	if (map == NULL)
		sl_error("Error reading map from file.");
	if (!map_check(map))
	{
		map_destroy(&map);
		sl_error("That map does not constitute a valid level.");
	}
	//mlx_loop(mlx);
	map_view(map);
	map_destroy(&map);
	//mlx_terminate(mlx);
	return (0);
}
