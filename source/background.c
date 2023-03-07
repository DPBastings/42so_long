/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:37:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 11:37:44 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"

static void	draw_bg_element(t_point p, t_game *game);

void	draw_bg(t_game *game)
{
	t_point	p;
	int32_t	xstart;

	p.y = HUD_H - game->view.port_min.y % GRID_H;
	xstart = -(game->view.port_min.x % GRID_W);
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
	mlx_image_t	*fill;
	mlx_image_t	*bg;
	int32_t		id;

	fill = game->sprites[SPR_FILLER]->image;
	bg = game->sprites[SPR_BG]->image;
	if (p.x >= game->view.port_min.x && p.x < game->view.port_max.x
		&& p.y >= game->view.port_min.y && p.y < game->view.port_max.y)
	{
		id = mlx_image_to_window(game->mlx, bg, p.x, p.y);
		if (id == -1)
			sl_error(SL_MEMFAIL);
		mlx_set_instance_depth(&bg->instances[id], -1);
	}
	else
	{
		id = mlx_image_to_window(game->mlx, fill, p.x, p.y);
		if (id == -1)
			sl_error(SL_MEMFAIL);
		mlx_set_instance_depth(&fill->instances[id], 0);
	}
}
