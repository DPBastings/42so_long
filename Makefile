# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/16 11:14:39 by dbasting      #+#    #+#                  #
#    Updated: 2023/01/16 18:19:43 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := so_long

OS := $(shell uname -s)

SRC_DIR := ./source/
OBJ_DIR := ./object/
HDR_DIR := ./header/
LIB_DIR := ./lib/

SRC_FILES := main.c\
	canvas.c\
	draw.c\
	load_assets.c
OBJ_FILES := $(SRC_FILES:.c=.o)
HDR_FILES := draw.h\
	parse.h
LIB_FILES := libftprintf.a
ifeq ($(OS),Linux)
    LIB_FILES += libmlx_Linux.a
else
    LIB_FILES += libmlx.a
endif

CFLAGS ?= -Wall -Wextra -Werror -I$(HDR_DIR) -I$(LIB_DIR) -L$(HDR_DIR) -L$(LIB_DIR)
ifeq ($(OS),Linux)
    MLX_FLAGS := -L/usr/lib -lXext -lX11 -lm -lz
endif
ifeq ($(OS),Darwin)
    MLX_FLAGS := -framework OpenGL -framework AppKit
endif
.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: all
	@echo "Bonus is basis, vrind."

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES))
	$(MAKE) --directory=$(LIB_DIR)
	@$(CC) $(CFLAGS) $^ $(addprefix $(LIB_DIR),$(LIB_FILES)) $(MLX_FLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HDR_DIR),$(HDR_FILES))
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(MAKE) --directory=$(LIB_DIR) clean
	@rm -f $(OBJ_DIR)*.o

fclean: clean
	$(MAKE) --directory=$(LIB_DIR) fclean
	@rm -f $(NAME)

re: fclean all
