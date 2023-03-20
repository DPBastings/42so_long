/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:53:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 16:52:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "ft_math.h"
#include "point.h"
#include <stdint.h>

#define VMARGIN	240

static void	objects_reposition(t_map *map, t_point diff);
static void	object_reposition(t_object *obj, t_point diff);

void	view_update(t_point diff, t_game *game)
{
	if (game->view.origin.x + diff.x < 0)
		diff.x = 0;
	if (game->view.origin.x + diff.x > game->view.origin_max.x)
		diff.x = game->view.origin_max.x - game->view.origin.x;
	if (game->view.origin.y + diff.y < 0)
		diff.y = 0;
	if (game->view.origin.y + diff.y > game->view.origin_max.y)
		diff.y = game->view.origin_max.y - game->view.origin.y;
	if (diff.x == 0 && diff.y == 0)
		return ;
	objects_reposition(game->map, diff);
	game->view.origin.x += diff.x;
	game->view.origin.y += diff.y;
}

void	view_centre(t_point anchor, t_game *game)
{
	t_point	diff;

	diff = game->view.origin;
	diff.x += anchor.x - ((game->view.port_max.x + game->view.port_min.x) / 2);
	diff.y += anchor.y - ((game->view.port_max.y + game->view.port_min.y) / 2);
	view_update(diff, game);
}

void	view_shift(t_point anchor, t_game *game)
{
	t_point	diff;

	set_point(&diff, 0, 0);
	if (anchor.x < game->view.port_min.x + VMARGIN)
		diff.x = anchor.x - (game->view.port_min.x + VMARGIN);
	else if (anchor.x > game->view.port_max.x - VMARGIN)
		diff.x = anchor.x - (game->view.port_max.x - VMARGIN);
	if (anchor.y < game->view.port_min.y + VMARGIN)
		diff.y = anchor.y - (game->view.port_min.y + VMARGIN);
	else if (anchor.y > game->view.port_max.y - VMARGIN)
		diff.y = anchor.y - (game->view.port_max.y - VMARGIN);
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
		object_reposition(obj->below, diff);
	}
}
