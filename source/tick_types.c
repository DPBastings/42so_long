#include "so_long.h"

#include "geometry.h"

static const uint32_t	g_lookup_dir[N_DIRS * N_DIM] = {
	0, -1,
	1, 0,
	0, 1,
	-1, 0,
};

static void	plyr_check_collisions(t_object *plyr, t_game *game);
t_point	point_get_adjacent(t_point p, uint32_t dir);

void	object_tick_default(t_object *obj, void *param)
{
	t_game			*game;
	mlx_instance_t	*instance;

	game = param;
	if (obj->moving > 0)
	{
		instance = &obj->sprite->image->instances[obj->instance_id];
		instance->x += g_lookup_dir[obj->facing * N_DIM + X] * (GRID_W / MOVEMENT_SPEED);
		instance->y += g_lookup_dir[obj->facing * N_DIM + Y] * (GRID_H / MOVEMENT_SPEED);
		if (instance->x % GRID_W == 0 && instance->y % GRID_H == 0)
		{
			object_place(obj, game->map, point_get_adjacent(obj->position, obj->facing));
			obj->moving--;
		}
	}
	obj->ticked = true;
}

void	object_tick_player(t_object *plyr, void *param)
{
	t_game		*game;

	game = param;
	object_tick_default(plyr, param);
	if (sprite_animation_is_done(plyr->sprite) || plyr->moving == 0)
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
	plyr_check_collisions(plyr, game);
}

void	plyr_check_collisions(t_object *plyr, t_game *game)
{
	t_object	*other;

	other = plyr->obj_below;
	if (other)
	{
		if (other->type == OBJ_COLL)
		{
			plyr->obj_below = other->obj_below;
			object_collect(game, &other);
		}
		else if (other->type == OBJ_EXIT && game->score == game->score_max)
			game_exit(game);
	}
}
