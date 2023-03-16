/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:43:05 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/14 14:48:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42/MLX42.h"
#include "mlx42_string.h"
#include <stdint.h>

#define	MARGIN	8

void	text_static_render(t_hud *hud, mlx_t *mlx, t_texture *font)
{
	uint32_t	p[2];
	
	p[0] = 0;
	p[1] = 0;
	hud->text = mlx_new_image(mlx, HUD_W - 2 * MARGIN, HUD_H - 2 * MARGIN);
	if (hud->text == NULL)
		sl_error(SL_MEMFAIL);
	string_to_image("LEVEL:\nSCORE:\nMOVES:\n", hud->text, (uint32_t *)p, font);
}
