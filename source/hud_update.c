/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_update.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:18:29 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/27 13:58:51 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_hud.h"
#include "sl_utils.h"

#include <float.h>
#include "mlx42_utils.h"
#include <stdint.h>

void	hud_text_update(t_hud *hud, char const *str, uint32_t p[2])
{
	t_style		style;

	p[0] *= CHAR_W;
	p[1] *= 1.5 * CHAR_H;
	style.font = hud->font;
	style.size = 1;
	style.colour = TEXT_COLOUR_B;
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
