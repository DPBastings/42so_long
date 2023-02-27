/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_adapt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:34:54 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/27 15:12:05 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include <float.h>

unsigned int	sprite_adapt_wall(t_object *obj, void *param)
{
	(void) obj;
	(void) param;
	return (0);
}

unsigned int	sprite_adapt_coll(t_object *obj, void *param)
{
	t_game	*game;
	int32_t	factor;

	game = param;
	factor = game->seed / (obj->position.x * obj->position.y + 1);
	printf("%d -> %d\n", game->seed, factor);
	obj->dir = ((factor - (int32_t) obj->position.y) % 2 * 2);
	//obj->sprite->image->instances[obj->instance_id].y += (factor % 8 - 4);
	return (factor % N_COLL_SPR);
}
