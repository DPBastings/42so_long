/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:53:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/27 14:15:08 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_view.h"
#include "so_long.h"

#include "ft_math.h"
#include "point.h"
#include <stdint.h>

#define VMARGIN	216

static void	objects_reposition(t_map *map, t_point diff);
static void	object_reposition(t_object *obj, t_point diff);

void	view_update(t_view *view, t_point diff, t_map *map)
{
	if (view->origin.x + diff.x < 0)
		diff.x = 0;
	if (view->origin.x + diff.x > view->origin_max.x)
		diff.x = view->origin_max.x - view->origin.x;
	if (view->origin.y + diff.y < 0)
		diff.y = 0;
	if (view->origin.y + diff.y > view->origin_max.y)
		diff.y = view->origin_max.y - view->origin.y;
	if (diff.x == 0 && diff.y == 0)
		return ;
	objects_reposition(map, diff);
	view->origin.x += diff.x;
	view->origin.y += diff.y;
}

void	view_centre(t_view *view, t_point anchor, t_map *map)
{
	t_point	diff;

	diff = view->origin;
	diff.x += anchor.x - ((view->port_max.x + view->port_min.x) / 2);
	diff.y += anchor.y - ((view->port_max.y + view->port_min.y) / 2);
	view_update(view, diff, map);
}

void	view_shift(t_view *view, t_point anchor, t_map *map)
{
	t_point	diff;

	set_point(&diff, 0, 0);
	if (anchor.x < view->port_min.x + VMARGIN)
		diff.x = anchor.x - (view->port_min.x + VMARGIN);
	else if (anchor.x > view->port_max.x - VMARGIN)
		diff.x = anchor.x - (view->port_max.x - VMARGIN);
	if (anchor.y < view->port_min.y + VMARGIN)
		diff.y = anchor.y - (view->port_min.y + VMARGIN);
	else if (anchor.y > view->port_max.y - VMARGIN)
		diff.y = anchor.y - (view->port_max.y - VMARGIN);
	view_update(view, diff, map);
}

static void	objects_reposition(t_map *map, t_point diff)
{
	t_upoint	p;

	p.y = 0;
	while (p.y < map->dims.y)
	{
		p.x = 0;
		while (p.x < map->dims.x)
		{
			object_reposition(*map_index(map, p), diff);
			p.x++;
		}
		p.y++;
	}
}

static void	object_reposition(t_object *obj, t_point diff)
{
	if (obj == NULL)
		return ;
	obj->sprite->image->instances[obj->instance_id].x -= diff.x;
	obj->sprite->image->instances[obj->instance_id].y -= diff.y;
	object_reposition(obj->below, diff);
}
