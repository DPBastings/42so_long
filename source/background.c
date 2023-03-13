/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:37:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 16:29:15 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include "MLX42/MLX42.h"

static void	draw_bg_element(t_point p, t_game *game);

void	bg_render(t_game *game)
{
	t_point	p;
	int32_t	xstart;

	p.y = HUD_H - game->view.port_min.y % GRID_H;
	xstart = 0 - (game->view.port_min.x % GRID_W);
	while (p.y < SCREEN_H)
	{
		p.x = xstart;
		while (p.x < SCREEN_W)
		{
			draw_bg_element(p, game);
			p.x += GRID_W;
		}
		p.y += GRID_H;
	}
}

static void	draw_bg_element(t_point p, t_game *game)
{
	mlx_image_t	*img;
	int32_t		id;

	if (p.x >= game->view.port_min.x && p.x < game->view.port_max.x
		&& p.y >= game->view.port_min.y && p.y < game->view.port_max.y)
		img = game->sprites[SPR_BG]->image;
	else
		img = game->sprites[SPR_FILLER]->image;
	id = mlx_image_to_window(game->mlx, img, p.x, p.y);
	if (id == -1)
		sl_error(SL_MEMFAIL);
	mlx_set_instance_depth(&img->instances[id], Z_BG0);
}
