#include "so_long.h"

#include "geometry.h"
#include <stdint.h>

int32_t	view_xview(int32_t x, t_view view)
{
	x = x + view.offset.x - view.origin.x;
	return (x);
}

int32_t view_yview(int32_t y, t_view view)
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

t_point	view_pview(t_point p, t_view view)
{
	p.x = view_xview(p.x, view);
	p.y = view_yview(p.y, view);
	return (p);
}
