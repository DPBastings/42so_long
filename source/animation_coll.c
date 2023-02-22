#include "so_long.h"

#include <stdbool.h>

#define AMPLITUDE 6

void	sprite_animate_coll(t_sprite *spr, void *param)
{
	t_game		*game;
	uint32_t	y;
	int32_t		instance;

	game = param;
	sprite_overlay_gradient(spr, game->gradient);
	instance = 0;
	y = spr->frame % (AMPLITUDE * 4);
	while (instance < spr->image->count)
	{
		if (y >= AMPLITUDE * 3)
			spr->image->instances[instance].y -= 1;
		else if (y < AMPLITUDE)
			spr->image->instances[instance].y += 1;
		instance++;
	}
	spr->frame++;
}
