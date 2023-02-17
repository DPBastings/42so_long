#include "so_long.h"
#include "geometry.h"

unsigned int	sprite_shift_wall(t_object *obj, void *param)
{
	(void) obj;
	(void) param;
	return (0);
}

unsigned int	sprite_shift_coll(t_object *obj, void *param)
{
	(void) param;
	return ((obj->position.x + obj->position.y) % 4);
}
