#ifndef MLX42_UTILS_H
# define MLX42_UTILS_H

# include "MLX42/MLX42.h"

typedef enum {
	R = 0,
	G,
	B,
	A,
	BPP,
}	t_rgba;

uint8_t	*pixel_get(uint8_t *pixels, uint32_t wh[2], uint32_t x, uint32_t y);
void	pixel_overlay(uint8_t *pixel, uint8_t *overlay);

#endif
