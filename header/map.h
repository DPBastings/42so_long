/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:15 by dbasting      #+#    #+#                 */
/*   Updated: 2022/12/16 16:20:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"
# include <stddef.h>

typedef struct	s_map {
	char	**objs;
	size_t	w;
	size_t	h;
}	t_map;

# define OBJ_NONE '0'
# define OBJ_WALL '1'
# define OBJ_COLL 'C'
# define OBJ_EXIT 'E'
# define OBJ_STRT 'P'
# define OBJ_ENMY_H 'X'
# define OBJ_ENMY_V 'Y'

# define CHECK_EXIT 1
# define CHECK_COLL 2
# define CHECK_STRT 4

int		map_check(t_map *map);
t_map	*map_read(char const *filename);
void	map_destroy(t_map **map);

#endif
