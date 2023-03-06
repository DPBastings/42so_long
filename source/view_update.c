/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:53:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 16:36:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "ft_math.h"
#include "geometry.h"
#include <stdint.h>

#define VIEW_BORDER_W	192
#define VIEW_BORDER_H	192

static void	objects_reposition(t_map *map, t_point diff);
static void	object_reposition(t_object *obj, t_point diff);

void	view_update(t_point diff, t_game *game)
{
	if (!(diff.x || diff.y))
		return ;
	objects_reposition(game->map, diff);
	game->view.origin.x += diff.x;
	game->view.origin.y += diff.y;
}

void	view_centre(t_point anchor, t_game *game)
{
	t_point	diff;

	diff = game->view.origin;
	if (game->view.offset.x == 0)
		diff.x += ft_intmin(2,
				anchor.x - (VIEW_MAXW / 2),
				game->map->dims.x * GRID_W - VIEW_MAXW);
	if (game->view.offset.y == HUD_H)
		diff.y += ft_intmin(2,
				anchor.y - (SCREEN_H / 2),
				game->map->dims.y * GRID_H - VIEW_MAXH);
	view_update(diff, game);
}

void	view_shift(t_point anchor, t_game *game)
{
	t_point	diff;

	set_point(&diff, 0, 0);
	if (game->view.offset.x == 0)
	{
		if (anchor.x <= VIEW_BORDER_W && game->view.origin.x > 0)
			diff.x = anchor.x - VIEW_BORDER_W;
		else if (anchor.x >= VIEW_MAXW - VIEW_BORDER_W
			&& game->view.origin.x <= game->map->dims.x * GRID_W - VIEW_MAXW)
			diff.x = anchor.x - (VIEW_MAXW - VIEW_BORDER_W);
	}
	if (game->view.offset.y == HUD_H)
	{
		if (anchor.y <= VIEW_BORDER_H && game->view.origin.y > 0)
			diff.y = anchor.y - VIEW_BORDER_H;
		else if (anchor.y >= VIEW_MAXH - VIEW_BORDER_H
			&& game->view.origin.y < game->map->dims.y * GRID_H - VIEW_MAXH)
			diff.y = anchor.y - (VIEW_MAXH - VIEW_BORDER_H);
	}
	view_update(diff, game);
}

static void	objects_reposition(t_map *map, t_point diff)
{
	t_upoint	p;
	t_object	*obj;

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
	if (obj)
	{
		obj->sprite->image->instances[obj->instance_id].x -= diff.x;
		obj->sprite->image->instances[obj->instance_id].y -= diff.y;
		object_reposition(obj->obj_below, diff);
	}
}
