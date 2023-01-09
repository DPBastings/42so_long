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
	@echo $(wildcard $(basename $@)/include/$@)
	@echo $(wildcard $(addsuffix $(INC_DIR)$@,./$(basename $@)))
	@$(if $(wildcard $(addsuffix $(INC_DIR),$(basename $@))),\
		$(call execute,ln -fs ./$(addprefix $(basename $@)/$(INC_DIR),$@) $@),\
		$(call execute,ln -fs ./$(addprefix $(basename $@)/,$@) $@))

clean:
	$(foreach d,$(LIB_DIRS),$(call execute,-$(MAKE) --directory=$(d) clean))

fclean:
	$(foreach d,$(LIB_DIRS),$(call execute,-$(MAKE) --directory=$(d) fclean))
	@rm -f $(LIB_ARCS) $(LIB_HDRS)

re: fclean all
