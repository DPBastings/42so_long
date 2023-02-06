/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   charmap.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/02/06 16:14:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARMAP_H
# define CHARMAP_H

# include "geometry.h"

# define MAP_EXT	".ber"

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
# define CHR_STRT	'P'
# define CHR_ENMYH	'X'
# define CHR_ENMYV	'Y'

# define CHECK_EXIT	1
# define CHECK_COLL	2
# define CHECK_STRT	4

int			charmap_check(t_charmap *map);
int			charmap_check_walls(t_charmap *map);
int			charmap_check_object(t_charmap *map);
int			charmap_check_path(t_charmap *map);
t_charmap	*charmap_read(char const *filename);
t_charmap	*charmap_copy(t_charmap *map);
void		charmap_destroy(t_charmap **map);

#endif
