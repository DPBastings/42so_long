/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   view.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 11:47:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/06 11:52:09 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "geometry.h"
#include <stdint.h>

int32_t	view_xview(int32_t x, t_view view)
{
	x = x + view.offset.x - view.origin.x;
	return (x);
}

int32_t	view_yview(int32_t y, t_view view)
{
	y = y + view.offset.y - view.origin.y;
	return (y);
}

uint32_t	view_xgrid(int32_t x, t_view view)
{
	x = x - view.offset.x + view.origin.x;
	if (x < 0)
		sl_error(SL_GENERIC);
	return ((uint32_t) x);
}

uint32_t	view_ygrid(int32_t y, t_view view)
{
	y = y - view.offset.y + view.origin.y;
	if (y < 0)
		sl_error(SL_GENERIC);
	return ((uint32_t) y);
}
