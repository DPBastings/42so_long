/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_utils.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 12:08:31 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/21 12:22:11 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_UTILS_H
# define SL_UTILS_H

# include "point.h"

typedef enum e_dirs {
	DIR_N = 0,
	DIR_NE,
	DIR_E,
	DIR_SE,
	DIR_S,
	DIR_SW,
	DIR_W,
	DIR_NW,
	N_DIRS,
}	t_dir;

t_dir		dir_invert(t_dir dir);

void		instance_move(mlx_instance_t *instance, t_dir dir, uint32_t speed);
t_point		instance_to_point(mlx_instance_t instance);
t_upoint	upoint_get_adjacent(t_upoint p, uint32_t dir);

char		*sl_itoa(uint32_t value, char *str);

#endif
