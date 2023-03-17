/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_bar_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:44:56 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 16:59:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"
#include "sl_image.h"
#include "sl_error.h"

#include "point.h"
#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>
#include <stdlib.h>

#define BAR_MARGIN	6

static void	bar_render(t_bar *bar, mlx_t *mlx);
static void	measure_draw(mlx_image_t *img, mlx_texture_t *txr);

t_bar	*hud_bar_init(t_hud *hud, mlx_t *mlx, mlx_texture_t **txrs)
{
	t_bar		*bar;
	t_upoint	gridsize;

	bar = malloc(sizeof(t_bar));
	if (bar == NULL)
		sl_error(SL_MEMFAIL);
	set_point(&bar->origin, hud->origin.x + 48, hud->origin.y + 96);
	bar->overlay = image_init(mlx, HUD_W - 2 * GRID_W, GRID_H);
	set_upoint(&gridsize, GRID_W, GRID_H);
	image_tile(bar->overlay, txrs[TXR_PROGRESS_BAR], (uint32_t *)&gridsize);
	bar->measure = image_init(mlx,
			bar->overlay->width - 2 * BAR_MARGIN,
			bar->overlay->height - 4 * BAR_MARGIN);
	measure_draw(bar->measure, txrs[TXR_GRADIENT]);
	bar->mask = image_init(mlx, bar->measure->width, bar->measure->height);
	pixels_set(bar->mask->pixels, bar->mask->width * bar->mask->height,
		0xFF0F0F0F);
	bar_render(bar, mlx);
	bar->percent = 0.0;
	return (bar);
}

void	hud_bar_destroy(t_bar **bar, mlx_t *mlx)
{
	mlx_delete_image(mlx, (*bar)->overlay);
	mlx_delete_image(mlx, (*bar)->measure);
	mlx_delete_image(mlx, (*bar)->mask);
	free(*bar);
	*bar = NULL;
}

static void	bar_render(t_bar *bar, mlx_t *mlx)
{
	int32_t	id;

	id = image_render(mlx, bar->overlay, bar->origin.x, bar->origin.y);
	mlx_set_instance_depth(&bar->overlay->instances[id], Z_HUD3);
	id = image_render(mlx, bar->mask,
			bar->origin.x + BAR_MARGIN, bar->origin.y + BAR_MARGIN + 4);
	mlx_set_instance_depth(&bar->mask->instances[id], Z_HUD2);
	id = image_render(mlx, bar->measure,
			bar->origin.x + BAR_MARGIN, bar->origin.y + BAR_MARGIN + 4);
	mlx_set_instance_depth(&bar->measure->instances[id], Z_HUD1);
}

static void	measure_draw(mlx_image_t *img, mlx_texture_t *txr)
{
	t_upoint		p;
	uint8_t			*px;

	p.y = 0;
	while (p.y < img->height)
	{
		p.x = 0;
		while (p.x < img->width)
		{
			px = &img->pixels[(p.y * img->width + p.x) * BPP];
			pixels_set(px, 1, CLR_RED);
			pixel_overlay(px, gradient_read(txr, p.x / 4 + p.y / 2));
			p.x++;
		}
		p.y++;
	}
}
