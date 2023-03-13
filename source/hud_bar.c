/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_bar.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:18:29 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/13 16:38:52 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <float.h>
#include "mlx42_utils.h"
#include <stdint.h>

void	hud_bar_fill(t_bar *bar, double percent)
{
	uint32_t	y;
	uint32_t	width;

	y = 0;
	width = (uint32_t)(percent * bar->bar->width);
	printf("%F %u\n", percent, width);
	while (y < bar->bar->height)
	{
		ft_memset(&bar->bar->pixels[y * bar->bar->width * BPP], 127, width * BPP);
		y++;
	}
}
