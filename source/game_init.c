/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 11:39:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static t_texture	*gradient_load(void);
static void			screen_init(t_game *game);

t_game	*game_init(char const *filename)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (game == NULL)
		sl_error(SL_MEMFAIL);
	game->map = map_load(filename);
	map_check(game->map);
	game->score_max = map_get_maxscore(game->map);
	screen_init(game);
	game->gradient = gradient_load();
	game->textures = textures_load(game);
	game->sprites = sprites_init(game);
	game->seed = seed_get(game);
	sprites_setup(game);
	draw_bg(game);
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

static void	screen_init(t_game *game)
{
	if (game->map->dims.x * GRID_W < SCREEN_W)
		game->view.offset.x += (VIEW_MAXW - game->map->dims.x * GRID_W) / 2;
	game->view.offset.y = HUD_H;
	if (game->map->dims.y * GRID_H < SCREEN_H)
		game->view.offset.y += (VIEW_MAXH - game->map->dims.y * GRID_H) / 2;
	game->mlx = mlx_init(SCREEN_W, SCREEN_H, SL_TITLE, false);
	if (game->mlx == NULL)
		sl_error(SL_MEMFAIL);
}

void	game_end(t_game *game)
{
	if (game == NULL)
		return ;
	map_destroy(&game->map);
	sprites_destroy(&game->sprites, game->mlx);
	if (game->gradient)
		mlx_delete_texture(game->gradient);
	textures_destroy(&game->textures);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game);
}
