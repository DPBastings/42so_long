# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/27 15:22:52 by dbasting      #+#    #+#                  #
#    Updated: 2023/03/27 15:22:53 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

OS	= $(shell uname -s)

LIB	= libft libftprintf libmlx
HDR	= libft.h ft_math.h libftprintf.h
ARC = libft.a libftprintf.a libmlx42.a
DIR = ./libft ./libftprintf

.PHONY: all clean fclean re

all: $(ARC) $(HDR) ./MLX42/

define execute
$(1)

endef

libf%.a:
	@$(MAKE) --directory=./$(basename $@)/
	@ln -fs ./$(basename $@)/$@ ./$@

libf%.h:
	@ln -fs ./$(basename $@)/include/$@ $@

ft_math.h:
	@ln -fs ./libft/include/ft_math.h

libmlx42.a:
	@cmake -S ./libmlx42 -B ./libmlx
	@cmake --build ./libmlx -j4
	@ln -fs ./libmlx/libmlx42.a

./MLX42/:
	@ln -fs ./libmlx42/include/MLX42/ ./MLX42

clean:
	@$(foreach d,$(DIR),$(call execute,-$(MAKE) --directory=$(d) clean))
	@cmake --build ./libmlx/ --target clean

fclean: clean
	@$(foreach d,$(DIR),$(call execute,-$(MAKE) --directory=$(d) fclean))
	@rm -f $(ARC) $(HDR)
	@rm -f ./MLX42
	@rm -rf ./libmlx/

re: fclean all
