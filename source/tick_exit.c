/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tick_exit.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 15:42:36 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 11:46:26 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdbool.h>
#include <stdint.h>

void	tick_exit(t_object *exit, void *param)
{
	(void) param;
	if (exit->sprite->animator == sprite_animate
		&& sprite_animation_is_done(exit->sprite))
		exit->sprite->animator = sprite_animate_pass;
}
