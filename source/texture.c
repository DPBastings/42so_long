/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:30:38 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/10 13:51:00 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "geometry.h"

#include "libft.h"
#include "MLX42/MLX42.h"
#include <stdlib.h>

static char const	*g_texture_files[N_TEXTURES] = {
	"",
	"./assets/textures/verve.png",
	"./assets/textures/verve_idle.png",
	"./assets/textures/verve_walk_up.png",
	"./assets/textures/verve_walk_right.png",
	"./assets/textures/verve_walk_down.png",
	"./assets/textures/verve_walk_left.png",
	"./assets/textures/orb.png",
	"./assets/textures/door.png",
	"./assets/textures/vortex.png",
	"./assets/textures/wall_tiles.png",
	"./assets/textures/background.png",
	"./assets/textures/hud_bg.png",
	"./assets/textures/hud_bar.png",
};

void	textures_load(t_game *game)
{
	size_t		i;

	i = 1;
	game->textures = ft_calloc(N_TEXTURES, sizeof(t_texture *));
	if (game->textures == NULL)
		sl_error(SL_MEMFAIL);
	while (i < N_TEXTURES)
	{
		game->textures[i] = texture_load(g_texture_files[i]);
		if (game->textures[i] == NULL)
		{
			textures_destroy(&game->textures);
			sl_error(SL_MEMFAIL);
		}
		i++;
	}
}

t_texture	*texture_load(char const *filename)
{
	t_texture	*texture;

	texture = mlx_load_png(filename);
	if (texture == NULL || texture->width % GRID_W)
		sl_error(SL_BADASS);
	return (texture);
}

void	textures_destroy(t_texture ***textures)
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
