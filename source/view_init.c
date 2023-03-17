/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 12:04:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 13:31:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"

#include "point.h"
#include "ft_math.h"

static void	apply_offset(t_view *view);

void	view_init(t_game *game)
{	
	t_upoint	pixel_dims;

	pixel_dims.x = game->map->dims.x * GRID_W;
	pixel_dims.y = game->map->dims.y * GRID_H;
	if (pixel_dims.x < VIEW_MAXW)
		game->view.port_min.x = (VIEW_MAXW - pixel_dims.x) / 2;
	if (pixel_dims.y < VIEW_MAXH)
		game->view.port_min.y = (VIEW_MAXH - pixel_dims.y) / 2;
	game->view.port_max.x = VIEW_MAXW - game->view.port_min.x;
	game->view.port_max.y = VIEW_MAXH - game->view.port_min.y;
	game->view.origin_max.x = ft_intmax(2,
			0, pixel_dims.x - game->view.port_max.x);
	game->view.origin_max.y = ft_intmax(2,
			0, pixel_dims.y - game->view.port_max.y);
	apply_offset(&game->view);
}

static void	apply_offset(t_view *view)
{
	view->port_min.y += HUD_H;
	view->port_max.y += HUD_H;
}
