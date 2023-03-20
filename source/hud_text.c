/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_text.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:43:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 14:43:56 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"
#include "sl_image.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>

#define MARGIN	12

void	hud_text_init(t_hud *hud, mlx_t *mlx)
{
	uint32_t	p[2];
	t_style		style;
	char		maxscore[MAX_DIGITS + 1];
	int32_t		id;

	p[0] = 0;
	p[1] = 0;
	hud->text = image_init(mlx,
			hud->bg->width / 4 * 3 - 2 * MARGIN, 96);
	style.font = hud->font;
	style.size = 1;
	style.colour = 0xAEA7A0FF;
	string_to_image("Level:\n"
		"Moves: \n"
		"Score:           /\n", hud->text, p, &style);
	hud_update_moves(hud, 0);
	hud_update_score(hud, 0);
	id = image_render(mlx, hud->text,
			hud->origin.x + MARGIN, hud->origin.y + MARGIN);
	mlx_set_instance_depth(&hud->text->instances[id], Z_HUD1);
}
