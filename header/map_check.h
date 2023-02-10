/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 16:14:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CHECK_H
# define MAP_CHECK_H

# include "so_long.h"
# include "geometry.h"

# define CHR_ALL	"01CEPXY"
# define CHR_NONE	'0'

# define CHECK_EXIT	1
# define CHECK_COLL	2
# define CHECK_PLYR	4

int			map_check_walls(t_map *map);
int			map_check_object(t_map *map);
int			map_check_path(t_map *map);

#endif
