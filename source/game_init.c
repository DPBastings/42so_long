/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/20 12:59:28 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static mlx_texture_t	*gradient_load(void);
static mlx_t			*screen_init(unsigned int width, unsigned int height);
static void				game_abort(t_game *game, int errno);

t_game	*game_init(char const *filename)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (game == NULL)
		sl_error(SL_MEMFAIL);
	ft_printf("Loading map...\n");
	game->map = map_load(filename);
	if (!map_check(game->map))
		game_abort(game, SL_INVMAP);
	game->score_max = map_get_maxscore(game->map);
	game->mlx = screen_init(game->map->dims.w * GRID_W,
			game->map->dims.h * GRID_H);
	if (game->mlx == NULL)
		game_abort(game, SL_MEMFAIL);
	ft_printf("Loading assets...\n");
	game->gradient = gradient_load();
	game->textures = textures_load(game);
	game->sprites = sprites_init(game);
	sprites_bind(game);
	ft_printf("Good luck!\n");
	return (game);
}

static mlx_texture_t	*gradient_load(void)
{
	mlx_texture_t	*gradient;

	gradient = mlx_load_png("./assets/textures/gradient_rainbow.png");
	if (gradient == NULL)
		sl_error(SL_MEMFAIL);
	return (gradient);
}

static mlx_t	*screen_init(unsigned int width, unsigned int height)
{
	if (width < SCREEN_MIN_W)
		width = SCREEN_MIN_W;
	if (height < SCREEN_MIN_H)
		height = SCREEN_MIN_H;
	return (mlx_init(width, height, SL_TITLE, false));
}

static void	game_abort(t_game *game, int errno)
{
	game_end(game);
	sl_error(errno);
}

void	game_end(t_game *game)
{
	if (game == NULL)
		return ;
	ft_printf("Unloading map...\n");
	map_destroy(&game->map);
	ft_printf("Unloading assets...\n");
	sprites_destroy(&game->sprites, game->mlx);
	if (game->gradient)
		mlx_delete_texture(game->gradient);
	textures_destroy(&game->textures);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game);
	ft_printf("Goodbye!\n");
}
