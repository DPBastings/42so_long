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

void	text_static_render(t_game *game)
{
	mlx_image_t			*img;

	img = mlx_put_string(game->mlx, "goeiedagschotel", 48, 48);
	mlx_image_to_window(game->mlx, img, 0, 0);
}
