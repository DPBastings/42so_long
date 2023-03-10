/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_render.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 13:48:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/10 14:38:56 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include <stdint.h>

#define BAR_MARGIN 4

static void	bar_render(t_bar *bar, mlx_t *mlx); 

void	hud_render(t_hud *hud, mlx_t *mlx)
{
	int32_t	id;
	
	id = mlx_image_to_window(mlx, hud->bg, 0, 0);
	if (id == -1)
		sl_error(SL_MEMFAIL);
	mlx_set_instance_depth(&hud->bg->instances[id], Z_HUD0);
	bar_render(hud->bar, mlx);
}

static void	bar_render(t_bar *bar, mlx_t *mlx)
{
	int32_t	id;
	
	id = mlx_image_to_window(mlx, bar->frame, bar->origin.x, bar->origin.y);
	if (id == -1)
		sl_error(SL_MEMFAIL);
	mlx_set_instance_depth(&bar->frame->instances[id], Z_HUD2);
	id = mlx_image_to_window(mlx, bar->bar,
			bar->origin.x + BAR_MARGIN, bar->origin.y + BAR_MARGIN);
	if (id == -1)
		sl_error(SL_MEMFAIL);
	mlx_set_instance_depth(&bar->frame->instances[id], Z_HUD1);
}
