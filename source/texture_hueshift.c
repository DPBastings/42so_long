/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_hueshift.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/24 13:05:44 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 13:36:02 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sl_graphics.h"

#include "MLX42/MLX42.h"
#include "mlx42_utils.h"
#include <stdint.h>

#define N_PLYRTXR 4

void	textures_plyr_hueshift(mlx_texture_t **txrs, uint32_t frame)
{
	t_txr_id const	ids[N_PLYRTXR] = {
		TXR_PLYR_IDLE, TXR_PLYR_WALK_R, TXR_PLYR_WALK_D, TXR_PLYR_WALK_L};
	uint32_t		i;

	i = 0;
	while (i < N_PLYRTXR)
	{
		texture_hueshift(txrs[ids[i]], txrs[TXR_GRADIENT], frame);
		i++;
	}
}
