/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_adapt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:34:54 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 14:18:38 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"

unsigned int	sprite_adapt_wall(t_object *obj, void *param)
{
	(void) obj;
	(void) param;
	return (0);
}

unsigned int	sprite_adapt_coll(t_object *obj, void *param)
{
	(void) param;
	obj->dir = ((obj->position.x + obj->position.y) % 2 * 2);
	return ((obj->position.x + obj->position.y) % N_COLL_SPR);
}
