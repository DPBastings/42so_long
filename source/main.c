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

#include "sl_test.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		sl_error(SL_INVARGS);
	game = game_init(argv[1]);
	hook_set(game);
	mlx_loop(game->mlx);
	game_end(game);
	return (0);
}
