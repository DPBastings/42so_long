#include "so_long.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include "geometry.h"

void	sprite_overlay_gradient(t_sprite *sprite, mlx_texture_t *gradient)
{
	t_point	p;
	t_plane	a;

	if (sprite == NULL || gradient == NULL)
		return ;
	set_plane(&a, GRID_W, GRID_H);
	p.y = 0;
	while (p.y < sprite->image->height)
	{
		p.x = 0;
		while (p.x < sprite->image->width)
		{
			pixel_overlay(pixel_get(sprite->image->pixels, (uint32_t *)a,
					p.x, p.y),
				gradient_read(sprite->gradient, p.x));
			p.x++;
		}
		p.y++;
	}
}

uint8_t	*gradient_read(mlx_texture_t *gradient, uint32_t i)
{
	if (gradient == NULL)
		return (NULL);
	i %= gradient->width * gradient->height - 1;
	return (&gradient->pixels[i * BPP]);
}
