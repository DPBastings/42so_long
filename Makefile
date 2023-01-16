# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/16 11:14:39 by dbasting      #+#    #+#                  #
#    Updated: 2023/01/16 14:41:42 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := so_long

OS := $(shell uname -s)

SRC_DIR := ./source/
OBJ_DIR := ./object/
HEADER_DIR := ./header/
LIB_DIR := ./lib/

SRC_FILES := main.c\
	canvas.c\
	draw.c
OBJ_FILES := $(SRC_FILES:.c=.o)
HEADER_FILES := draw.h\
	parse.h
LIB_FILES := libmlx.a\
	libftprintf.a

CFLAGS ?= -Wall -Wextra -Werror -I$(HEADER_DIR) -I$(LIB_DIR)
ifeq ($(OS),Linux)
	FRAMEWORK := -lXext -X11
endif
ifeq ($(OS),Darwin)
	FRAMEWORK := -framework OpenGL -framework AppKit
endif
.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: all
	@echo "Bonus is basis, vrind."

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES))
	#$(MAKE) --directory=$(LIB_DIR)
	$(CC) $(CFLAGS) $(FRAMEWORK) $^ $(addprefix $(LIB_DIR),$(LIB_FILES)) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HEADER_DIR),$(HEADER_FILES))
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OBJ_DIR)*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
