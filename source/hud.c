/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:44:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 16:15:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "mlx42_utils.h"
#include <stdlib.h>

static void	hud_bg_init(t_game *game);
static void	hud_bg_draw(mlx_image_t *bg, mlx_texture_t *txr, t_upoint dst);
static void	hud_text_init(t_game *game);

void	hud_init(t_game *game)
{
	game->hud = malloc(sizeof(t_hud));
	if (game->hud == NULL)
		sl_error(SL_MEMFAIL);
	hud_bg_init(game);
	hud_text_init(game);
	hud_bar_init(game, GRID_W, 96);
}

static void	hud_bg_init(t_game *game)
{
	t_upoint	p;

	game->hud->bg = mlx_new_image(game->mlx, HUD_W, HUD_H);
	if (game->hud->bg == NULL)
		sl_error(SL_MEMFAIL);
	p.y = 0;
	while (p.y < HUD_H)
	{
		p.x = 0;
		while (p.x < HUD_W)
		{
			hud_bg_draw(game->hud->bg, game->textures[TXR_HUD_BG], p);
			p.x += GRID_W;
		}
		p.y += GRID_H;
	}
}

static void	hud_bg_draw(mlx_image_t *bg, mlx_texture_t *txr, t_upoint dst)
{
	t_upoint	src;

	set_upoint(&src, 0, 0);
	if (dst.x >= bg->width - GRID_W)
		src.x = 2 * GRID_W;
	else if (dst.x > 0)
		src.x = GRID_W;
	if (dst.y >= bg->height - GRID_H)
		src.y = 2 * GRID_H;
	else if (dst.y > 0)
		src.y = GRID_H;
	texture_area_copy_to_image(bg, txr, (uint32_t *)&dst, (uint32_t *)&src);
}

static void	hud_text_init(t_game *game)
{
	return ;
}

void	hud_destroy(t_hud **hud, mlx_t *mlx)
{
	hud_bar_destroy(&(*hud)->bar, mlx);
	mlx_delete_image(mlx, (*hud)->bg);
	free(*hud);
	*hud = NULL;
}
