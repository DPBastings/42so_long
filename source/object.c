/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:48:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 12:03:02 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include "libft.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

enum e_obj_vars {
	OBJ_Z	= 0,
	OBJ_DIR,
	OBJ_SPEED,
	OBJ_PASSABLE,
	N_OBJ_VARS,
};

static int32_t	g_lut_obj_vars[N_OBJS][N_OBJ_VARS] = {
{Z_FG,		DIR_UP,		0,	false,},
{Z_PLYR,	DIR_DOWN,	0,	true,},
{Z_COLL0,	DIR_UP,		1,	true,},
{Z_MAP,		DIR_UP,		0,	true,},
{Z_MAP,		DIR_UP,		0,	false,},
{Z_ENMY,	DIR_RIGHT,	6,	true,},
{Z_ENMY,	DIR_DOWN,	6,	true,},
{Z_ENMY,	DIR_DOWN,	6,	true,},
{Z_BG1,		DIR_UP,		0,	true,},};

/* t_object *object_init(unsigned int type)
 * Initializes a new object of type `type`.
 * Returns NULL on failure.
 */
t_object	*object_init(t_obj_id type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (new == NULL)
		return (NULL);
	new->type = type;
	set_upoint(&new->position, -1, -1);
	new->z = g_lut_obj_vars[type][OBJ_Z];
	new->dir = g_lut_obj_vars[type][OBJ_DIR];
	new->speed = g_lut_obj_vars[type][OBJ_SPEED];
	new->passable = g_lut_obj_vars[type][OBJ_PASSABLE];
	new->sprite = NULL;
	new->instance_id = -1;
	new->obj_below = NULL;
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
