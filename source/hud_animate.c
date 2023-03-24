/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_animate.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 15:11:44 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 13:19:00 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_hud.h"
#include "so_long.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"

static void	hud_bar_fill(t_bar *bar);

void	hud_bar_animate(t_bar *bar, t_game *game)
{
	bar_hueshift(bar->measure, game->textures[TXR_GRADIENT], game->ticks);
	if (bar->percent < (double) game->score / game->score_max)
	{
		bar->percent += 1.0 / game->score_max / 12;
		if (bar->percent >= 1.0)
			bar->percent = 1.0;
		hud_bar_fill(bar);
	}
}

static void	hud_bar_fill(t_bar *bar)
{
	uint32_t	y;

	y = 0;
	while (y < bar->mask->height)
	{
		pixels_set_channel(&bar->mask->pixels[y * bar->mask->width * BPP],
			(uint32_t)(bar->percent * bar->mask->width),
			A,
			0);
		y++;
	}
}
