/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/13 17:49:22 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CHECK_H
# define MAP_CHECK_H

# include "so_long.h"
# include "geometry.h"

# define CHR_ALL	"0PCE1P"
# define CHR_NONE	'0'

# define CHECK_EXIT	1
# define CHECK_PLYR	2
# define CHECK_COLL 4

int			map_check_walls(t_map *map);
int			map_check_objects(t_map *map);
int			map_check_path(t_map *map);

#endif
