/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:53:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/10 15:46:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "ft_math.h"
#include "geometry.h"
#include <stdint.h>

#define MARGIN	240

//static void	sprites_reposition(t_sprite **sprites, t_point diff);
//static void	sprite_reposition(t_sprite *sprite, t_point diff);
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
	if (anchor.x < game->view.port_min.x + MARGIN)
		diff.x = anchor.x - (game->view.port_min.x + MARGIN);
	else if (anchor.x > game->view.port_max.x - MARGIN)
		diff.x = anchor.x - (game->view.port_max.x - MARGIN);
	if (anchor.y < game->view.port_min.y + MARGIN)
		diff.y = anchor.y - (game->view.port_min.y + MARGIN);
	else if (anchor.y > game->view.port_max.y - MARGIN)
		diff.y = anchor.y - (game->view.port_max.y - MARGIN);
	view_update(diff, game);
}

/*static void	sprites_reposition(t_sprite **sprites, t_point diff)
{
	t_spr_id	spr;

	spr = 1;
	while (spr < N_SPRITES)
		sprite_reposition(sprites[spr++], diff);
}

static void	sprite_reposition(t_sprite *sprite, t_point diff)
{
	int32_t	i;

	i = 0;
	while (i < sprite->image->count)
	{
		sprite->image->instances[i].x -= diff.x;
		sprite->image->instances[i].y -= diff.y;
		if (sprite->image->instances[i].z <= Z_BG1)
		{
			if (sprite->image->instances[i].x < -GRID_W)
				sprite->image->instances[i].x += VIEW_MAXW + 2 * GRID_W;
			else if (sprite->image->instances[i].x > VIEW_MAXW + GRID_W)
				sprite->image->instances[i].x -= VIEW_MAXW + 2 * GRID_W;
			if (sprite->image->instances[i].y < -GRID_H)
				sprite->image->instances[i].y += VIEW_MAXH + 2 * GRID_H;
			else if (sprite->image->instances[i].y > VIEW_MAXH + GRID_H)
				sprite->image->instances[i].y -= VIEW_MAXH + 2 * GRID_H;
		}
		i++;
	}
}*/

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
