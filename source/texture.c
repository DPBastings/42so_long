/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 14:31:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sl_error.h"
#include "point.h"

#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static char const	*g_texture_files[N_TEXTURES] = {
	"",
	"./assets/textures/gradient_rainbow.png",
	"./assets/textures/verve.png",
	"./assets/textures/verve_idle.png",
	"./assets/textures/verve_walk_up.png",
	"./assets/textures/verve_walk_right.png",
	"./assets/textures/verve_walk_down.png",
	"./assets/textures/verve_walk_left.png",
	"./assets/textures/grauwling_walk_up.png",
	"./assets/textures/grauwling_walk_right.png",
	"./assets/textures/grauwling_walk_down.png",
	"./assets/textures/grauwling_walk_left.png",
	"./assets/textures/orb.png",
	"./assets/textures/door.png",
	"./assets/textures/vortex.png",
	"./assets/textures/wall_tiles.png",
	"./assets/textures/background.png",
	"./assets/textures/hud_bg.png",
	"./assets/textures/logo.png",
	"./assets/textures/hud_bar.png",
};

mlx_texture_t	**textures_load(void)
{
	mlx_texture_t	**txrs;
	t_txr_id		i;

	i = 1;
	txrs = ft_calloc(N_TEXTURES, sizeof(mlx_texture_t *));
	if (txrs == NULL)
		sl_error(SL_MEMFAIL);
	while (i < N_TEXTURES)
	{
		txrs[i] = texture_load(g_texture_files[i]);
		i++;
	}
	return (txrs);
}

mlx_texture_t	*texture_load(char const *filename)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(filename);
	if (texture == NULL)
		sl_error(SL_MEMFAIL);
	return (texture);
}

void	textures_destroy(mlx_texture_t ***textures)
{
	size_t	i;

	if (*textures == NULL)
		return ;
	i = 1;
	while (i < N_TEXTURES)
		mlx_delete_texture((*textures)[i++]);
	free(*textures);
	*textures = NULL;
}
