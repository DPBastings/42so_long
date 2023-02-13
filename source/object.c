/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:48:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 16:14:39 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <stdlib.h>

/* t_object *object_init(unsigned int type)
 * Initializes a new object of type `type`.
 * Returns NULL on failure.
 */
t_object	*object_init(unsigned int type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->id = 0;
	return (new);
}

/* int object_is_passable(t_object *obj)
 * Returns whether `obj` is passable.
 */
int	object_is_passable(t_object *obj)
{
	return (obj == NULL
		|| (obj->type != OBJ_WALL && obj->type != OBJ_NONE));
}

/* t_object *object_move(t_object *`obj`, t_map *`map`,
 * 						 unsigned int xdelta, unsigned int ydelta)
 * Modifies the position of `obj` on `map` by `xdelta` and `ydelta` units.
 * If that position is passable, the return value will correspond to the object
 * that was there previously (or to NULL, if it was empty space).
 * Returns NOWHERE if the position was out of bounds or otherwise impassable.
 */
t_object	*object_move(t_object *obj, t_map *map,
	unsigned int xdelta, unsigned int ydelta)
{
	t_object	*other;
	t_point		np;

	set_point(&np, obj->position.x + xdelta, obj->position.y + ydelta);
	other = *map_index(map, np);
	if (object_is_passable(other))
	{
		*map_index(map, obj->position) = NULL;
		*map_index(map, np) = obj;
		obj->position = np;
		obj->sprite->image->instances[obj->id].x = np.x * GRID_W;
		obj->sprite->image->instances[obj->id].y = np.y * GRID_H;
		return (other);
	}
	return (NOWHERE);
}

void	object_destroy(t_object **obj)
{
	if (*obj == NULL)
		return ;
	if ((*obj)->sprite)
		(*obj)->sprite->image->instances[(*obj)->id].enabled = false;
	free(*obj);
	*obj = NULL;
}
