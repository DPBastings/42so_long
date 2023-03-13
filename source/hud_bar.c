/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_bar.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:44:56 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 12:01:11 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>
#include <stdlib.h>

#define BAR_MARGIN	4

static void	bar_frame_init(mlx_t *mlx, t_bar *bar, mlx_texture_t *txr);
static void	bar_frame_fill(mlx_image_t *img, mlx_texture_t *txr, t_upoint dst);
static void	bar_render(mlx_t *mlx, t_bar *bar);

void	hud_bar_init(t_game *game, int32_t x, int32_t y)
{
	game->hud->bar = malloc(sizeof(t_hud));
	if (game->hud->bar == NULL)
		sl_error(SL_MEMFAIL);
	set_point(&game->hud->bar->origin, x, y);
	bar_frame_init(game->mlx, game->hud->bar,
		game->textures[TXR_PROGRESS_BAR_FRAME]);
	game->hud->bar->bar = mlx_new_image(game->mlx,
			game->hud->bar->frame->width - 2 * BAR_MARGIN,
			game->hud->bar->frame->height - 2 * BAR_MARGIN);
	if (game->hud->bar->bar == NULL)
		sl_error(SL_MEMFAIL);
}

static void	bar_frame_init(mlx_t *mlx, t_bar *bar, mlx_texture_t *txr)
{
	t_upoint	p;

	bar->frame = mlx_new_image(mlx, HUD_W - 2 * GRID_W, GRID_H);
	if (bar->frame == NULL)
		sl_error(SL_MEMFAIL);
	set_upoint(&p, 0, 0);
	while (p.x < bar->frame->width)
	{
		bar_frame_fill(bar->frame, txr, p);
		p.x += GRID_W;
	}
}	

static void	bar_frame_fill(mlx_image_t *img, mlx_texture_t *txr, t_upoint dst)
{
	t_upoint	src;

	set_upoint(&src, 0, 0);
	if (dst.x >= img->width - GRID_W)
		src.x = 2 * GRID_W;
	else if (dst.x > 0)
		src.x = GRID_W;
	texture_area_copy_to_image(img, txr, (uint32_t *)&dst, (uint32_t *)&src);
}

void	hud_bar_destroy(t_bar **bar, mlx_t *mlx)
{
	mlx_delete_image(mlx, (*bar)->frame);
	mlx_delete_image(mlx, (*bar)->bar);
	free(*bar);
	*bar = NULL;
}
