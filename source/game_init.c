/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:21:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/27 13:57:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"
#include "sl_graphics.h"
#include "sl_hud.h"
#include "sl_view.h"

#include "libft.h"
#include "MLX42/MLX42.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static char const	*filename_truncate(char const *filename);
static void			hud_static_text_update(t_hud *hud,
						char const *name, uint32_t maxscore);
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
	view_init(&game->view, game->map->dims);
	game->textures = textures_load();
	game->font = texture_load("./assets/textures/font.png");
	game->sprites = sprites_init(game->mlx, game->textures);
	game->seed = seed_get(game);
	game->hud = hud_init(game->mlx, game->textures, game->font);
	hud_static_text_update(game->hud,
		filename_truncate(filename), game->score_max);
	bg_render(game->mlx, game->sprites, game->view);
	sprites_setup(game);
	view_centre(&game->view,
		instance_to_point(game->map->player->sprite->image->instances[0]),
		game->map);
	textures_plyr_hueshift(game->textures, game->seed);
	return (game);
}

void	game_end(t_game *game)
{
	if (game == NULL)
		return ;
	message_destroy(&game->msg, game->mlx);
	map_destroy(&game->map);
	hud_destroy(&game->hud, game->mlx);
	sprites_destroy(&game->sprites, game->mlx);
	textures_destroy(&game->textures);
	mlx_delete_texture(game->font);
	mlx_terminate(game->mlx);
	free(game);
}

static char const	*filename_truncate(char const *filename)
{
	size_t	i;

	i = ft_strlen(filename);
	while (i--)
	{
		if (filename[i] == '/')
			return (filename + i + 1);
	}
	return (filename);
}

static void	hud_static_text_update(t_hud *hud,
				char const *name, uint32_t maxscore)
{
	uint32_t	hud_offset[2];
	char		score[MAX_DIGITS + 1];

	hud_offset[0] = 7;
	hud_offset[1] = 0;
	hud_text_update(hud, name, hud_offset);
	hud_offset[0] = 7 + MAX_DIGITS + 1;
	hud_offset[1] = 2;
	score[MAX_DIGITS] = '\0';
	sl_itoa(maxscore, score);
	hud_text_update(hud, score, hud_offset);
}

static void	screen_init(t_game *game)
{
	game->mlx = mlx_init(SCREEN_W, SCREEN_H, SL_TITLE, false);
	if (game->mlx == NULL)
		sl_error(SL_MEMFAIL);
}
