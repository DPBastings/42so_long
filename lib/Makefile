OS	= $(shell uname -s)

LIB	= libft libftprintf libmlx
HDR	= libft.h libftprintf.h mlx.h
ARC = libft.a libftprintf.a
ifeq ($(OS),Linux)
    ARC += libmlx_Linux.a
else
    ARC += libmlx.a
endif
DIR = $(addprefix ./,$(addsuffix /,$(LIB)))

.PHONY: all clean fclean re

all: $(ARC) $(HDR)

libmlx_Linux.a:
	cd ./libmlx && ./configure
	@ln -fs ./libmlx/$@ $@

libmlx.a:
	@$(MAKE) --directory=./libmlx/
	@ln -fs ./libmlx/$@ $@

libf%.a:
	$(MAKE) --directory=./$(basename $@)/
	@ln -fs ./$(basename $@)/$@ ./$@

libf%.h:
	@ln -fs ./$(basename $@)/include/$@ $@

mlx.h:
	@ln -fs ./libmlx/$@ $@

clean:
	$(foreach d,$(DIR),$(call execute,-$(MAKE) --directory=$(d) clean))

fclean: clean
	$(foreach d,$(DIR),$(call execute,-$(MAKE) --directory=$(d) fclean))
	@rm -f $(ARC) $(HDR)

re: fclean all
