OS	= $(shell uname -s)

LIB	= libftprintf libmlx
HDR	= libftprintf.h mlx.h
ARC = libftprintf.a
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

libftprintf.a:
	$(MAKE) --directory=./$(basename $@)/
	@ln -fs ./$(basename $@)/$@ ./$@

libftprintf.h:
	@ln -fs ./libftprintf/include/$@ $@

mlx.h:
	@ln -fs ./libmlx/$@ $@

clean:
	$(foreach d,$(DIR),$(call execute,-$(MAKE) --directory=$(d) clean))

fclean: clean
	$(foreach d,$(DIR),$(call execute,-$(MAKE) --directory=$(d) fclean))
	@rm -f $(ARC) $(HDR)

re: fclean all
