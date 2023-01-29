#include "geometry.h"

t_point	get_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_plane	get_plane(int w, int h)
{
	t_plane	plane;

	plane.w = w;
	plane.h = h;
	return (plane);
}
