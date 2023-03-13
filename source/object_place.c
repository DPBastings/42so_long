/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_place.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:00:55 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 16:10:28 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include <stdbool.h>
#include <stdint.h>

void	object_place(t_object *obj, t_map *map, t_upoint p)
{
	t_object	**slot;

	slot = map_index(map, p);
	object_remove(obj, map);
	obj->position = p;
	object_insert_above(obj, *slot);
	*slot = obj;
}

void	object_insert_above(t_object *obj, t_object *other)
{
	obj->below = other;
	if (other)
	{
		obj->above = other->above;
		other->above = obj;
		if (obj->above)
			obj->above->below = obj;
	}
}

void	object_insert_below(t_object *obj, t_object *other)
{
	obj->above = other;
	if (other)
	{
		obj->below = other->below;
		other->below = obj;
		if (obj->below)
			obj->below->above = obj;
	}
}

void	object_remove(t_object *obj, t_map *map)
{
	if (obj->below)
		obj->below->above = obj->above;
	if (obj->above)
		obj->above->below = obj->below;
	else
		*map_index(map, obj->position) = obj->below;
	obj->above = NULL;
	obj->below = NULL;
}

bool	object_align_grid(t_object *obj, t_game *game)
{
	mlx_instance_t	instance;
	t_upoint		p;

	instance = obj->sprite->image->instances[obj->instance_id];
	set_upoint(&p,
		view_xgrid(instance.x, game->view),
		view_ygrid(instance.y, game->view));
	if (p.x % GRID_W == 0 && p.y % GRID_H == 0)
	{
		set_upoint(&p, p.x / GRID_W, p.y / GRID_H);
		object_place(obj, game->map, p);
		return (true);
	}
	return (false);
}
