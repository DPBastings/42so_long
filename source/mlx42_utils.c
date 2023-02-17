#include "MLX42/MLX42.h"
#include "mlx42_utils.h"

#include "ft_math.h"
#include <float.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

uint8_t	*pixel_get(uint8_t *pixels, uint32_t wh[2], uint32_t x, uint32_t y)
{
	if (texture == NULL || x >= wh[0] || y >= wh[1])
		return (NULL);
	return (&pixels[(y * wh[0] + x) * BPP]);
}

void	pixel_hueshift(uint8_t *pixel, uint8_t *overlay)
{
	double	factor;
	size_t	i;

	if (pixel == NULL || overlay == NULL)
		return ;
	factor = (double) ft_maxuint(3, pixel[R], pixel[G], pixel[B]) / UCHAR_MAX;
	i = R;
	while (i < A)
	{
		pixel[i] = (uint8_t)(factor * overlay[i]);
		i++;
	}
}