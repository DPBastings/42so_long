/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 13:14:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"
#include "MLX42/MLX42.h"

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
