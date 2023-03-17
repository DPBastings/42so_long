/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 14:07:22 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 12:44:05 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

#include <stdint.h>

t_point	*set_point(t_point *point, int32_t x, int32_t y)
{
	point->x = x;
	point->y = y;
	return (point);
}

t_upoint	*set_upoint(t_upoint *upoint, uint32_t x, uint32_t y)
{
	upoint->x = x;
	upoint->y = y;
	return (upoint);
}
