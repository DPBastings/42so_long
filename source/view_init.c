/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 12:04:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 15:45:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_view.h"
#include "sl_hud.h"

#include "point.h"
#include "ft_math.h"

static void	apply_offset(t_view *view);

void	view_init(t_view *view, t_upoint map_dims)
{	
	map_dims.x *= GRID_W;
	map_dims.y *= GRID_H;
	if (map_dims.x < VIEW_MAXW)
		view->port_min.x = (VIEW_MAXW - map_dims.x) / 2;
	if (map_dims.y < VIEW_MAXH)
		view->port_min.y = (VIEW_MAXH - map_dims.y) / 2;
	view->port_max.x = VIEW_MAXW - view->port_min.x;
	view->port_max.y = VIEW_MAXH - view->port_min.y;
	view->origin_max.x = ft_intmax(2,
			0, map_dims.x - view->port_max.x);
	view->origin_max.y = ft_intmax(2,
			0, map_dims.y - view->port_max.y);
	apply_offset(view);
}

static void	apply_offset(t_view *view)
{
	view->port_min.y += HUD_H;
	view->port_max.y += HUD_H;
}
