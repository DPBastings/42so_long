/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 16:14:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "so_long.h"
# include "geometry.h"

typedef struct	s_charmap {
	t_plane	dims;
	char	**objs;
}	t_charmap;

# define CHR_ALL	"01CEPXY"
# define CHR_FILL	"01CXY"

# define CHR_NONE	'0'
# define CHR_WALL	'1'
# define CHR_COLL	'C'
# define CHR_EXIT	'E'
# define CHR_PLYR	'P'
# define CHR_ENMYH	'X'
# define CHR_ENMYV	'Y'

# define CHECK_EXIT	1
# define CHECK_COLL	2
# define CHECK_PLYR	4

int			map_check(t_map *map);
int			map_check_walls(t_map *map);
int			map_check_object(t_map *map);
int			map_check_path(t_map *map);

#endif
