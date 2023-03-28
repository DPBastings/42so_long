/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 11:47:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/28 11:13:39 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"
#include "MLX42/MLX42.h"

/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	sl_leaks(void)
{
	printf("--- %d ---\n", getpid());
	system("leaks so_long");
}
*/

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
