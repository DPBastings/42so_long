#include "so_long.h"

#include <stdint.h>

typedef enum e_axis {
	X = 0,
	Y,
	N_DIM,
}	t_axis;

static const uint32_t	g_lookup_dir[N_DIRS * N_DIM] = {
	0, -1,
	1, 0,
	0, 1,
	-1, 0,
};

t_point	point_get_adjacent(t_point p, uint32_t dir)
{
	p.x += g_lookup_dir[dir * N_DIM + X];
	p.y += g_lookup_dir[dir * N_DIM + Y];
	return (p);
}

/* t_object *object_move(t_object *obj, t_map *map,
 * 						 unsigned int xdelta, unsigned int ydelta)
 * Modifies the position of `obj` on `map` by `xdelta` and `ydelta` units.
 * If that position is passable, the return value will correspond to the object
 * that was there previously (or to NULL, if it was empty space).
 * Returns NOWHERE if the position was out of bounds or otherwise impassable.
 */
t_object	*object_move(t_object *obj, t_map *map, uint32_t dir)
{
	t_object	*other;
	t_point		p;

	p = point_get_adjacent(obj->position, dir);
	other = *map_index(map, p);
	object_place(obj, map, p);
	obj->sprite->image->instances[obj->instance_id].x = p.x * GRID_W;
	obj->sprite->image->instances[obj->instance_id].y = p.y * GRID_H;
	return (other);
}

void	object_place(t_object *obj, t_map *map, t_point p)
{
	t_object	**coordinate;
	
	*map_index(map, obj->position) = obj->obj_below;
	coordinate = map_index(map, p);
	obj->obj_below = *coordinate;
	*coordinate = obj;
	obj->position = p;
}
