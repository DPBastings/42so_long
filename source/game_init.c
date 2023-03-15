/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 13:19:06 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <unistd.h>

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
	textures_load(game);
	font_load(game);
	game->sprites = sprites_init(game);
	game->seed = seed_get(game);
	hud_init(game);
	hud_render(game->hud, game->mlx);
	bg_render(game);
	sprites_setup(game);
	view_centre(
		instance_to_point(game->map->player->sprite->image->instances[0]),
		game);
	return (game);
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
	textures_destroy(&game->textures);
	mlx_delete_texture(game->font);
	mlx_terminate(game->mlx);
	free(game);
}
