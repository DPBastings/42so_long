/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 18:08:38 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/MLX42.h"
#include "charmap.h"

#include "sl_test.h"

int	main(int argc, char **argv)
{
	//mlx_t		*mlx;
	t_tilemap	*game;
	t_charmap	*map;

	if (argc != 2)
		sl_error(SL_INVARGS);
	//mlx = mlx_init(1258, 768, "The Bach Game", true);
	map = charmap_read(argv[1]);
	if (map == NULL)
		sl_error(SL_INVMAP);
	if (!charmap_check(map))
	{
		charmap_destroy(&map);
		sl_error(SL_INVMAP);
	}
	//mlx_loop(mlx);
	charmap_view(map);
	game = tilemap_init(map->dims);
	tilemap_set(game, map);
	tilemap_view(game);
	charmap_destroy(&map);
	//mlx_terminate(mlx);
	return (0);
}
