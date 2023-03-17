/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_bg.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:44:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 16:59:35 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"
#include "sl_error.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>
#include <stdlib.h>

static void	hud_bg_draw(mlx_image_t *bg, mlx_texture_t *txr, t_upoint dst);
static void	hud_bg_render(t_hud *hud, mlx_t *mlx);

void	hud_bg_init(t_hud *hud, mlx_t *mlx, mlx_texture_t **txrs)
{
	t_upoint	p;
	t_upoint	gridsize;

	hud->bg = mlx_new_image(mlx, HUD_W, HUD_H);
	if (hud->bg == NULL)
		sl_error(SL_MEMFAIL);
	set_upoint(&gridsize, GRID_W, GRID_H);
	image_tile(hud->bg, txrs[TXR_HUD_BG], (uint32_t *)&gridsize);
	hud_bg_render(hud, mlx);
}

static void	hud_bg_render(t_hud *hud, mlx_t *mlx)
{
	int32_t	id;

	id = mlx_image_to_window(mlx, hud->bg, hud->origin.x, hud->origin.y);
	if (id == -1)
		sl_error(SL_MEMFAIL);
	mlx_set_instance_depth(&hud->bg->instances[id], Z_HUD0);
}
