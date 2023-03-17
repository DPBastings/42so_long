/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_text.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:43:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 17:10:42 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_hud.h"
#include "sl_image.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>

#define MARGIN	12

void	text_static_render(t_hud *hud, mlx_t *mlx, mlx_texture_t *font)
{
	uint32_t	p[2];
	t_style		style;
	int32_t		id;

	p[0] = 0;
	p[1] = 0;
	hud->text = image_init(mlx,
			hud->bg->width - 2 * MARGIN, hud->bg->height - 2 * MARGIN);
	style.font = font;
	style.size = 1;
	style.colour = 0xFFA0AAAE;
	string_to_image("Level:", hud->text, (uint32_t *)p, &style);
	p[1] += 24;
	style.size = 2;
	string_to_image("Score:\nMoves:\n", hud->text, (uint32_t *)p, &style);
	id = image_render(mlx, hud->text,
			hud->origin.x + MARGIN, hud->origin.y + MARGIN);
	mlx_set_instance_depth(&hud->text->instances[id], Z_HUD1);
}
