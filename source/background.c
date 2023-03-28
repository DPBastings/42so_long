/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:37:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/28 11:14:35 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_graphics.h"
#include "sl_general.h"
#include "sl_hud.h"
#include "sl_image.h"
#include "sl_view.h"

#include "point.h"
#include "MLX42/MLX42.h"

static void	draw_bg_element(mlx_t *mlx, t_point p, t_sprite **sprites,
				t_view view);

void	bg_render(mlx_t *mlx, t_sprite **sprites, t_view view)
{
	t_point	p;

	p.y = HUD_H - view.port_max.y % GRID_H;
	while (p.y < SCREEN_H)
	{
		p.x = 0 - view.port_max.x % GRID_W;
		while (p.x < SCREEN_W)
		{
			draw_bg_element(mlx, p, sprites, view);
			p.x += GRID_W;
		}
		p.y += GRID_H;
	}
}

static void	draw_bg_element(mlx_t *mlx, t_point p, t_sprite **sprites,
	t_view view)
{
	mlx_image_t	*img;
	int32_t		id;

	if (p.x >= view.port_min.x && p.x < view.port_max.x
		&& p.y >= view.port_min.y && p.y < view.port_max.y)
		img = sprites[SPR_BG]->image;
	else
		img = sprites[SPR_FILLER]->image;
	id = image_render(mlx, img, p.x, p.y);
	mlx_set_instance_depth(&img->instances[id], Z_BG0);
}
