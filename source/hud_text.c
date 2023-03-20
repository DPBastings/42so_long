/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_text.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:43:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 12:34:36 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"
#include "sl_image.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>

#define MARGIN	12

void	hud_text_init(t_hud *hud, mlx_t *mlx, mlx_texture_t *font)
{
	uint32_t	p[2];
	t_style		style;
	int32_t		id;

	p[0] = 0;
	p[1] = 0;
	hud->text = image_init(mlx,
			hud->bg->width / 4 * 3 - 2 * MARGIN, 96);
	style.font = font;
	style.size = 1;
	style.colour = 0xAEA7A0FF;
	string_to_image("Level:\nScore:\nMoves:\n", hud->text, p, &style);
	id = image_render(mlx, hud->text,
			hud->origin.x + MARGIN, hud->origin.y + MARGIN);
	mlx_set_instance_depth(&hud->text->instances[id], Z_HUD1);
}
