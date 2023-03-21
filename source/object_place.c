/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_place.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:00:55 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 16:22:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_object.h"
#include "sl_view.h"

#include "point.h"
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
