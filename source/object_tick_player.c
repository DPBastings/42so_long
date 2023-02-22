#include "so_long.h"

#include <stdbool.h>

static void	plyr_change_sprites(t_object *plyr, t_game *game);
static void	plyr_check_collisions(t_object *plyr, t_game *game);

void	object_tick_player(t_object *plyr, void *param)
{
	t_game		*game;

	game = param;
	object_tick_default(plyr, param);
	plyr_change_sprites(plyr, game);	
	plyr_check_collisions(plyr, game);
}

static void	plyr_change_sprites(t_object *plyr, t_game *game)
{
	if (plyr->moving == false && sprite_animation_is_done(plyr->sprite))
	{
		game->lock_input = false;
		sprite_change(plyr, game->sprites[SPR_PLYR], game);
		plyr->sprite->frame = 0;
	}
	if (plyr->sprite == game->sprites[SPR_PLYR] && game->ticks % 48 == 0)
	{
		sprite_change(plyr, game->sprites[SPR_PLYR_IDLE], game);
		plyr->sprite->frame = 0;
	}
}	

static void	plyr_check_collisions(t_object *plyr, t_game *game)
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
