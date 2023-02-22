#include "so_long.h"

#include "geometry.h"
#include <stdint.h>

static t_obj_ticker	g_lookup_ticker[N_OBJS] = {
	object_tick_pass,
	plyr_tick,
	object_tick_pass,
	object_tick_pass,
	object_tick_pass
};

static void	object_tick(t_object *obj, void *param);

void	objects_tick(t_game *game)
{
	t_point	p;
	
	p.y = 0;
	while (p.y < game->map->dims.h)
	{
		p.x = 0;
		while (p.x < game->map->dims.w)
		{
			object_tick(*map_index(game->map, p), game);
			p.x++;
		}
		p.y++;
	}
}

static void	object_tick(t_object *obj, void *param)
{
	if (obj)
	{
		g_lookup_ticker[obj->type](obj, param);
		object_tick(obj->obj_below, param);
	}
}

void	object_tick_pass(t_object *obj, void *param)
{
	(void) obj;
	(void) param;
}

void	plyr_tick(t_object *plyr, void *param)
{
	t_game	*game;

	game = param;
	if (sprite_animation_is_done(plyr->sprite))
	{
		plyr->sprite->frame = 0;
		sprite_change(plyr, game->sprites[SPR_PLYR], game);
		game->lock_input = false;
	}
	if (plyr->sprite == game->sprites[SPR_PLYR] && game->ticks % 48 == 0)
	{
		sprite_change(plyr, game->sprites[SPR_PLYR_IDLE], game);
		plyr->sprite->frame = 0;
	}
}
