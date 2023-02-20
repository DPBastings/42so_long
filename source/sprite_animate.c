#include "so_long.h"

#include "mlx42_utils.h"
#include <math.h>

#define	HOVER_THRESHOLD	0.70
#define HOVER_PERIOD	16

void	sprite_animate(t_sprite *sprite)
{
	uint8_t	*src;
	uint8_t	*dst;
	t_point	p;

	p.x = sprite->frame * GRID_W % sprite->texture->width;
	p.y = 0;
	while (p.y < sprite->image->height)
	{
		src = &sprite->texture->pixels[(p.y * sprite->texture->width + p.x) * BPP];
		dst = &sprite->image->pixels[p.y * GRID_H * BPP];
		ft_memmove(dst, src, GRID_W * BPP);
		p.y++;
	}
	sprite->frame++;
}

void	sprite_animate_coll(t_sprite *sprite, t_game *game)
{
	double	y;
	int32_t	instance;

	sprite_overlay_gradient(sprite, game->gradient);
	instance = 0;
	y = sprite->frame % HOVER_PERIOD;
	while (instance < sprite->image->count)
	{
		if (y >= 12)
			sprite->image->instances[instance].y -= 1;
		else if (y < 4)
			sprite->image->instances[instance].y += 1;
		instance++;
	}
}
