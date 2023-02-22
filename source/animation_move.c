#include "so_long.h"

#include <stdbool.h>

void	sprite_animate_move(t_sprite *spr, void *param)
{
	t_game		*game;

	game = param;
	sprite_overlay_gradient(spr, game->gradient);
	instance = 0;
	y = spr->frame % AMPLITUDE;
	while (instance < spr->image->count)
	{
		if (y <= AMPLITUDE * 3)
			spr->image->instances[instance].y -= 1;
		else if (y > AMPLITUDE)
			spr->image->instances[instance].y += 1;
		instance++;
	}
	spr->frame++;
}


