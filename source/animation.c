#include "so_long.h"

#include "mlx42_utils.h"
#include <math.h>
#include <stdbool.h>

static t_spr_animator	g_lookup_animator[N_SPRITES] = {
	sprite_animate_pass,
	sprite_animate_pass,
	sprite_animate,
	sprite_animate,
	sprite_animate,
	sprite_animate,
	sprite_animate,
	sprite_animate_coll,
	sprite_animate_coll,
	sprite_animate_coll,
	sprite_animate_coll,
	sprite_animate_coll,
	sprite_animate_coll,
	sprite_animate_pass,
	sprite_animate_pass,
};

void	sprites_animate(t_game *game)
{
	uint32_t	id;

	id = 0;
	while (id < N_SPRITES)
	{
		g_lookup_animator[id](game->sprites[id], game);
		id++;
	}
}

void	sprite_animate_pass(t_sprite *spr, void *param)
{
	(void) spr;
	(void) param;
}

void	sprite_animate(t_sprite *spr, void *param)
{
	uint8_t	*src;
	uint8_t	*dst;
	t_point	p;

	(void) param;
	p.x = spr->frame * GRID_W % spr->texture->width;
	p.y = 0;
	while (p.y < spr->image->height)
	{
		src = &spr->texture->pixels[(p.y * spr->texture->width + p.x) * BPP];
		dst = &spr->image->pixels[p.y * GRID_H * BPP];
		ft_memmove(dst, src, GRID_W * BPP);
		p.y++;
	}
	spr->frame++;
}

bool	sprite_animation_is_done(t_sprite *spr)
{
	if (spr == NULL)
		return (false);
	return (spr->frame >= spr->frame_max);
	//return (spr->frame * GRID_W % spr->texture->width == 0);
}
