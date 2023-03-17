/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_load.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 12:10:58 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 12:31:17 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_check.h"

#include "libft.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static t_obj_id	chrtotype(char const chr);

t_object	*object_load(char chr, t_upoint p)
{
	t_object	*obj;
	t_obj_id	type;

	type = chrtotype(chr);
	obj = object_init(type);
	if (obj == NULL)
		sl_error(SL_MEMFAIL);
}

static t_obj_id	chrtotype(char const chr)
{
	char *const		chars = CHR_ALL;
	t_obj_id const	ids[N_CHR] = {OBJ_NONE, OBJ_PLYR, OBJ_COLL, OBJ_EXIT,
		OBJ_WALL, OBJ_ENMY, OBJ_ENMY, OBJ_ENMY};
	char			*ptr;

	ptr = ft_strchr(chars, chr);
	if (ptr == NULL)
		sl_error(SL_INVMAP_UNKNOWNOBJ);
	return (ids[(uint32_t)(ptr - chars)]);
}
