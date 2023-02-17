# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/16 11:14:39 by dbasting      #+#    #+#                  #
#    Updated: 2023/02/13 17:25:44 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long

OS 			:= $(shell uname -s)

SRC_DIR		:= ./source/
OBJ_DIR		:= ./object/
HDR_DIR		:= ./header/
LIB_DIR		:= ./lib/

SRC_FILES	:= main.c\
			error.c\
			game_init.c\
			game_status.c\
			geometry.c\
			hook.c\
			hook_close.c\
			hook_keys.c\
			map.c\
			map_check.c\
			map_check_path.c\
			map_load.c\
			map_search.c\
			movement.c\
			object.c\
			sprite.c\
			sprite_bind.c\
			sprite_shift.c\
			texture.c\
			\
			sl_test.c
OBJ_FILES	:= $(SRC_FILES:.c=.o)
HDR_FILES	:= so_long.h\
			map_check.h\
			geometry.h\
			\
			sl_test.h
LIB_FILES	:= libft.a\
			libftprintf.a\
			libmlx42.a

CFLAGS 		?= -Wall -Wextra -I$(HDR_DIR) -I$(LIB_DIR)
ifeq ($(OS),Linux)
	MLX_FLAGS := -lglfw -L/usr/lib -ldl -pthread
endif
ifeq ($(OS),Darwin)
	MLX_FLAGS := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: all
	@echo "Bonus is basis, vrind."

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES)) $(addprefix $(LIB_DIR),$(LIB_FILES)) 
	@$(CC) $(CFLAGS) -L$(HDR_DIR) -L$(LIB_DIR) $^ $(MLX_FLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(LIB_DIR),$(LIB_FILES)) $(addprefix $(HDR_DIR),$(HDR_FILES))
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $<

%.a:
	@$(MAKE) --directory=$(LIB_DIR)

clean:
	@$(MAKE) --directory=$(LIB_DIR) clean
	@rm -f $(OBJ_DIR)*.o

fclean: clean
	@$(MAKE) --directory=$(LIB_DIR) fclean
	@rm -f $(NAME)

re: fclean all
