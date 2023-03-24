/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_map_check.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/24 14:53:47 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_MAP_CHECK_H
# define SL_MAP_CHECK_H

# include "sl_object.h"
# include "sl_error.h"

# define SL_FILEEXT		".ber"

# ifdef BONUS
#  define CHR_ALL		"0PCE1HV"
#  define N_CHR			8
# else
#  define CHR_ALL		"0PCE1"
#  define N_CHR			6
# endif

# define CHR_NONE		'0'

# define CHECK_EXIT		1
# define CHECK_PLYR		2
# define CHECK_COLL		4

# define N_MAP_CHECKS	3

t_sl_errno	map_check_walls(t_map *map);
t_sl_errno	map_check_objects(t_map *map);
t_sl_errno	map_check_path(t_map *map);

#endif
