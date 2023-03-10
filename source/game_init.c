/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/10 14:06:41 by dbasting      ########   odam.nl         */
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
	view_init(game);
	game->gradient = gradient_load();
	textures_load(game);
	game->sprites = sprites_init(game);
	game->seed = seed_get(game);
	sprites_setup(game);
	hud_init(game);
	hud_render(game->hud, game->mlx);
	draw_bg(game);
	view_centre(
		instance_to_point(game->map->player->sprite->image->instances[0]),
		game);
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
	game->mlx = mlx_init(SCREEN_W, SCREEN_H, SL_TITLE, false);
	if (game->mlx == NULL)
		sl_error(SL_MEMFAIL);
}

void	game_end(t_game *game)
{
	if (game == NULL)
		return ;
	map_destroy(&game->map);
	hud_destroy(&game->hud, game->mlx);
	sprites_destroy(&game->sprites, game->mlx);
	if (game->gradient)
		mlx_delete_texture(game->gradient);
	textures_destroy(&game->textures);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game);
}
