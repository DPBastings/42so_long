LIB_NAMES := mlx\
	libftprintf
LIB_ARCS := $(addsuffix .a,$(LIB_NAMES))
LIB_DIRS := $(addprefix ./,$(addsuffix /,$(LIB_NAMES)))
LIB_HDRS := $(addsuffix .h,$(LIB_NAMES))
INC_DIR := include/

define execute
$(1)

endef

.PHONY: all clean fclean re

all: $(LIB_ARCS) $(LIB_HDRS)

%.a:
	$(MAKE) --directory=./$(basename $@)/
	@ln -fs ./$(basename $@)/$@ ./$@

%.h:
	@$(if $(wildcard $(addsuffix $@,$(addsuffix $(INC_DIR),$(basename $@)/))),\
		$(call execute,ln -fs ./$(addprefix $(basename $@)/$(INC_DIR),$@) $@),\
		$(call execute,ln -fs ./$(addprefix $(basename $@)/,$@) $@))

clean:
	$(foreach d,$(LIB_DIRS),$(call execute,-$(MAKE) --directory=$(d) clean))

fclean: clean
	$(foreach d,$(LIB_DIRS),$(call execute,-$(MAKE) --directory=$(d) fclean))
	@rm -f $(LIB_ARCS) $(LIB_HDRS)

re: fclean all
