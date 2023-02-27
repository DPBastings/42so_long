/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:48:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 14:41:53 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

//Lookup table for various t_object members.
typedef enum e_obj_param {
	P_OBJ_DIR = 0,
	P_OBJ_SPEED,
	P_OBJ_PASSABLE,
	N_OBJ_PARAMS,
}	t_obj_param;

static uint16_t	g_lookup_obj_params[N_OBJS * N_OBJ_PARAMS] = {
	0,	0,	false,
	2,	0,	true,
	0,	1,	true,
	0,	0,	true,
	0,	0,	false,
};

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
	set_point(&new->position, -1, -1);
	new->dir = g_lookup_obj_params[type * N_OBJ_PARAMS + P_OBJ_DIR];
	new->speed = g_lookup_obj_params[type * N_OBJ_PARAMS + P_OBJ_SPEED];
	new->passable = g_lookup_obj_params[type * N_OBJ_PARAMS + P_OBJ_PASSABLE];
	new->sprite = NULL;
	new->instance_id = -1;
	new->obj_below = NULL;
	if (new->type == OBJ_COLL)
		printf("%u %u\n", new->dir, new->speed);
	return (new);
}

/* int object_is_passable(t_object *obj)
 * Returns whether `obj` is passable.
 */
bool	object_is_passable(t_object *obj)
{
	return (obj == NULL || obj->passable);
}

void	object_destroy(t_object **obj)
{
	t_object	*below;

	if (*obj == NULL)
		return ;
	if ((*obj)->sprite)
		(*obj)->sprite->image->instances[(*obj)->instance_id].enabled = false;
	below = (*obj)->obj_below;
	free(*obj);
	*obj = below;
}
