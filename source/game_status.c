/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 17:20:53 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 12:05:39 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_message.h"
#include "sl_object.h"

#include "libftprintf.h"
#include "MLX42/MLX42.h"
#include <stdbool.h>
#include <stdint.h>

#define BORDER	192

static void	message_win(mlx_t *mlx, mlx_texture_t *bg, mlx_texture_t *font);
static void	message_lose(mlx_t *mlx, mlx_texture_t *bg, mlx_texture_t *font);

void	object_collect(t_game *game, t_object **obj)
{
	object_remove(*obj, game->map);
	object_destroy(obj);
	game->score++;
	hud_update_score(game->hud, game->score);
	ft_printf("Score: %10u of %10u\n", game->score, game->score_max);
}

void	game_win(t_game *game)
{
	game->lock_input = true;
	game->game_over = true;
	ft_printf("You've made it!\n");
	message_win(game->mlx, game->textures[TXR_HUD_BG], game->font);
}

void	game_lose(t_game *game)
{
	game->lock_input = true;
	game->game_over = true;
	ft_printf("Ow!\n");
	message_lose(game->mlx, game->textures[TXR_HUD_BG], game->font);
}

static void	message_win(mlx_t *mlx, mlx_texture_t *bg, mlx_texture_t *font)
{
	t_message 		*msg;
	uint32_t const 	xy[2] = {BORDER, BORDER};
	uint32_t const	wh[2] = {SCREEN_W - 2 * BORDER, SCREEN_H - 2 * BORDER};

	msg = message_init(mlx, bg, xy, wh);
	message_print_caption(msg, "Congratulations!", font);
	message_print_body(msg, "You've collected every Rainbow Orb\n"
			"and managed to make it to the exit. Hooray to colour!\n\n"
			"Press ESC to exit the game.", font);
}

static void	message_lose(mlx_t *mlx, mlx_texture_t *bg, mlx_texture_t *font)
{
	t_message 		*msg;
	uint32_t const 	xy[2] = {BORDER, BORDER};
	uint32_t const	wh[2] = {SCREEN_W - 2 * BORDER, SCREEN_H - 2 * BORDER};

	msg = message_init(mlx, bg, xy, wh);
	message_print_caption(msg, "Too bad!", font);
	message_print_body(msg, "You got caught by the conformist Grauwlingen.\n"
			"It's going to be an existence of drabness for you\n"
			"from now on...\n\n"
			"Press ESC to exit the game.", font);
}
