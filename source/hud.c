/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 12:44:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/17 13:30:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_hud.h"
#include "sl_error.h"

#include "mlx42_utils.h"
#include "point.h"
#include <stdlib.h>

t_hud	*hud_init(mlx_t *mlx, mlx_texture_t **txrs, mlx_texture_t *font)
{
	t_hud	*hud;
	
	hud = malloc(sizeof(t_hud));
	if (hud == NULL)
		sl_error(SL_MEMFAIL);
	set_point(&hud->origin, 0, 0);
	hud_bg_init(hud, mlx, txrs);
	text_static_render(hud, mlx, font);
	hud->bar = hud_bar_init(hud, mlx, txrs);
	return (hud);
}

void	hud_destroy(t_hud **hud, mlx_t *mlx)
{
	hud_bar_destroy(&(*hud)->bar, mlx);
	mlx_delete_image(mlx, (*hud)->text);
	mlx_delete_image(mlx, (*hud)->bg);
	free(*hud);
	*hud = NULL;
}
