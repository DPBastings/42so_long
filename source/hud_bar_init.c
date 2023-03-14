/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_bar_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:44:56 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 12:39:56 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>
#include <stdlib.h>

#define BAR_MARGIN	6

static void	bar_draw(mlx_t *mlx, t_bar *bar, mlx_texture_t **txrs);
static void	frame_draw(mlx_image_t *img, mlx_texture_t *txr, t_upoint dst);
static void	measure_draw(mlx_image_t *img, mlx_texture_t *txr);

void	hud_bar_init(t_game *game, int32_t x, int32_t y)
{
	game->hud->bar = malloc(sizeof(t_bar));
	if (game->hud->bar == NULL)
		sl_error(SL_MEMFAIL);
	set_point(&game->hud->bar->origin, x, y);
	game->hud->bar->filled = 0.0;
	game->hud->bar->frame = mlx_new_image(game->mlx,
			HUD_W - 2 * GRID_W,
			GRID_H);
	if (game->hud->bar->frame == NULL)
		sl_error(SL_MEMFAIL);
	game->hud->bar->bar = mlx_new_image(game->mlx,
			game->hud->bar->frame->width - (2 * BAR_MARGIN),
			game->hud->bar->frame->height - (4 * BAR_MARGIN));
	if (game->hud->bar->bar == NULL)
		sl_error(SL_MEMFAIL);
	game->hud->bar->mask = mlx_new_image(game->mlx,
			game->hud->bar->frame->width - (2 * BAR_MARGIN),
			game->hud->bar->frame->height - (4 * BAR_MARGIN));
	if (game->hud->bar->mask == NULL)
		sl_error(SL_MEMFAIL);
	bar_draw(game->mlx, game->hud->bar, game->textures);
}

static void	bar_draw(mlx_t *mlx, t_bar *bar, mlx_texture_t **txrs)
{
	uint8_t const	mask[BPP] = {10, 10, 10, 255};
	t_upoint		p;

	set_upoint(&p, 0, 0);
	while (p.x < bar->frame->width)
	{
		frame_draw(bar->frame, txrs[TXR_PROGRESS_BAR_FRAME], p);
		p.x += GRID_W;
	}
	measure_draw(bar->bar, txrs[TXR_GRADIENT]);
	pixels_set(bar->mask->pixels, bar->mask->width * bar->mask->height, mask);
}

static void	frame_draw(mlx_image_t *img, mlx_texture_t *txr, t_upoint dst)
{
	t_upoint	src;

	set_upoint(&src, 0, 0);
	if (dst.x >= img->width - GRID_W)
		src.x = 2 * GRID_W;
	else if (dst.x > 0)
		src.x = GRID_W;
	texture_area_copy_to_image(img, txr, (uint32_t *)&dst, (uint32_t *)&src);
}

static void	measure_draw(mlx_image_t *img, mlx_texture_t *txr)
{
	t_upoint		p;
	uint8_t			*px;
	uint8_t const	mask[BPP] = {255, 0, 0, 255};

	p.y = 0;
	while (p.y < img->height)
	{
		p.x = 0;
		while (p.x < img->width)
		{
			px = &img->pixels[(p.y * img->width + p.x) * BPP];
			pixels_set(px, 1, mask);
			pixel_overlay(px, gradient_read(txr, p.x / 4 + p.y / 2));
			p.x++;
		}
		p.y++;
	}
}

void	hud_bar_destroy(t_bar **bar, mlx_t *mlx)
{
	mlx_delete_image(mlx, (*bar)->frame);
	mlx_delete_image(mlx, (*bar)->bar);
	mlx_delete_image(mlx, (*bar)->mask);
	free(*bar);
	*bar = NULL;
}
