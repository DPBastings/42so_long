/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:48:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 15:49:06 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <stdlib.h>

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

int	object_is_passable(t_object *obj)
{
	return (obj == NULL
		|| (obj->type != OBJ_WALL && obj->type != OBJ_NONE));
}

/* t_object *object_move()
 * Return value corresponds to the object that previously occupied `newpos`
 * (either NULL or a passable object (i.e. a collectible).
 */
t_object	*object_move(t_object *obj, t_map *map, unsigned int xdelta, unsigned int ydelta)
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
	(*obj)->sprite->image->instances[(*obj)->id].enabled = false;
	free(*obj);
	*obj = NULL;
}
