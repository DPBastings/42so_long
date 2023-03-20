/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_bg.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:44:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 13:37:08 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"
#include "sl_image.h"
#include "sl_error.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include "point.h"
#include <stdint.h>

#define MARGIN	8

static void	hud_add_logo(t_hud *hud, mlx_t *mlx, mlx_texture_t *txr);
static void	hud_bg_render(t_hud *hud, mlx_t *mlx);

void	hud_bg_init(t_hud *hud, mlx_t *mlx, mlx_texture_t **txrs)
{
	t_upoint	p;
	t_upoint	gridsize;

	hud->bg = image_init(mlx, HUD_W, HUD_H);
	set_upoint(&gridsize, GRID_W, GRID_H);
	image_tile(hud->bg, txrs[TXR_HUD_BG], (uint32_t *)&gridsize);
	hud->logo = image_from_texture_init(mlx, txrs[TXR_LOGO]);
	hud_bg_render(hud, mlx);
}

static void	hud_bg_render(t_hud *hud, mlx_t *mlx)
{
	int32_t	id;

	id = image_render(mlx, hud->bg, hud->origin.x, hud->origin.y);
	mlx_set_instance_depth(&hud->bg->instances[id], Z_HUD0);
	id = image_render(mlx, hud->logo,
			hud->bg->width - hud->logo->width - MARGIN, MARGIN);
	mlx_set_instance_depth(&hud->logo->instances[id], Z_HUD1);
}
