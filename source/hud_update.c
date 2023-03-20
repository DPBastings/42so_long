/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_update.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:18:29 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 14:44:48 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"

#include <float.h>
#include "mlx42_utils.h"
#include <stdint.h>

static void	hud_bar_fill(t_bar *bar);

void	hud_text_update(t_hud *hud, char const *str, uint32_t p[2])
{
	t_style		style;

	p[0] *= CHAR_W;
	p[1] *= 1.5 * CHAR_H;
	style.font = hud->font;
	style.size = 1;
	style.colour = 0xA6907BFF;
	string_to_image(str, hud->text, p, &style);
}

void	hud_update_moves(t_hud *hud, uint32_t moves)
{
	uint32_t	hud_offset[2];
	char		str[MAX_DIGITS + 1];

	hud_offset[0] = 7;
	hud_offset[1] = 1;
	str[MAX_DIGITS] = '\0';
	sl_itoa(moves, str);
	hud_text_update(hud, str, hud_offset);
}

void	hud_update_score(t_hud *hud, uint32_t score)
{
	uint32_t	hud_offset[2];
	char		str[MAX_DIGITS + 1];

	hud_offset[0] = 7;
	hud_offset[1] = 2;
	str[MAX_DIGITS] = '\0';
	sl_itoa(score, str);
	hud_text_update(hud, str, hud_offset);
}

void	hud_bar_animate(t_bar *bar, t_game *game)
{
	bar_overlay_gradient(bar->measure, game->textures[TXR_GRADIENT],
		game->ticks);
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
