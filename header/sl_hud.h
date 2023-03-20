/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_hud.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 11:14:48 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/20 12:13:59 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_HUD_H
# define SL_HUD_H

# include <float.h>
# include "MLX42/MLX42.h"
# include "point.h"
# include <stdint.h>

# define HUD_W			1248
# define HUD_H			144
# define TEXT_COLOUR	0xFFEEEEEE

typedef struct s_bar {
	t_point		origin;
	mlx_image_t	*measure;
	mlx_image_t	*mask;
	mlx_image_t	*overlay;
	double		percent;
}	t_bar;

typedef struct s_hud {
	t_point		origin;
	mlx_image_t	*bg;
	mlx_image_t	*logo;
	mlx_image_t	*text;
	t_bar		*bar;
}	t_hud;

t_hud	*hud_init(mlx_t *mlx, mlx_texture_t **txrs, mlx_texture_t *font);
void	hud_bg_init(t_hud *hud, mlx_t *mlx, mlx_texture_t **txrs);
t_bar	*hud_bar_init(t_hud *hud, mlx_t *mlx, mlx_texture_t **txrs);
void	hud_text_init(t_hud *hud, mlx_t *mlx, mlx_texture_t *font);
void	hud_destroy(t_hud **hud, mlx_t *mlx);
void	hud_bar_destroy(t_bar **bar, mlx_t *mlx);

#endif
