/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_object.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 15:53:30 by dbasting      #+#    #+#                 */
/*   Updated: 2023/03/28 10:59:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_OBJECT_H
# define SL_OBJECT_H

# include "sl_utils.h"
# include "sl_graphics.h"

# include "libft.h"
# include <stdbool.h>
# include <stdint.h>

typedef enum e_obj_id {
	OBJ_NONE = 0,
	OBJ_PLYR,
	OBJ_COLL,
	OBJ_EXIT,
	OBJ_WALL,
	OBJ_ENMY_H,
	OBJ_ENMY_V,
	OBJ_ANIM,
	N_OBJS,
}	t_obj_id;

/* Object object.
 * @param type			This object's type ID.
 * @param dir			The direction this object is facing.
 * @param speed			The object's movement speed.
 * @param position		The object's position.
 * @param z				The object's Z coordinate.
 * @param bool			Whether this object can be ordinarly moved onto.
 * @param ticked		Whether this object has received a tick.
 * @param sprite		The object's current sprite.
 * @param instance_id	The ID of the image instance corresponding to this object.
 * @param above			The object above this object.
 * @param below			The object beneath this object.
 */
typedef struct s_object {
	t_obj_id		type;
	uint16_t		dir;
	uint16_t		speed;
	t_upoint		position;
	int32_t			z;
	bool			passable;
	bool			ticked;
	t_sprite		*sprite;
	int32_t			instance_id;
	struct s_object	*above;
	struct s_object	*below;
}	t_object;

/* Map object.
 * @param dims		The map's dimensions.
 * @param objs		A 2D array containing all grid positions.
 * @param player	The object corresponding to the player.
 * @param exit		The object corresponding to the exit.
 * @param none		A location corresponding to a location outside the map's bounds.
 */
typedef struct s_map {
	t_upoint	dims;
	t_object	***objs;
	t_object	*player;
	t_object	*exit;
	t_object	*none;
}	t_map;

t_object	*object_init(t_obj_id type);
t_object	**object_get_adjacent(t_object *obj, t_map *map, t_dir dir);
bool		obj_is_passable(t_object *object);
bool		obj_is_harmful(t_object *object);
void		object_move(t_object *obj);
void		object_place(t_object *obj, t_map *map, t_upoint p);
void		object_insert_above(t_object *obj, t_object *below);
void		object_insert_below(t_object *obj, t_object *above);
void		object_remove(t_object *obj, t_map *map);
void		object_destroy(t_object **obj);

t_map		*map_load(char const *filename);
t_map		*map_init(t_upoint dims);
void		map_setup(t_map *map, t_list *bytemap);
bool		map_check(t_map *map, uint32_t score_max);
uint32_t	map_get_maxscore(t_map *map);	
t_object	**map_index(t_map *map, t_upoint p);
void		map_destroy(t_map **map);

#endif
