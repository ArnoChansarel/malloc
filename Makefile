##### COLORS #####
BLUE = \033[1;35m
GREY = \033[3;31m
GREEN = \033[1;37m
RED = \033[1;31m
END = \033[0m

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

##### TARGETS #####
NAME = libft_malloc_$(HOSTTYPE).so
L_NAME = libft_malloc.so

##### PATH #####
SRCPATH = ./srcs
OBJPATH = $(SRCPATH)/obj
LIBFTPATH = ./libft

##### LIBS #####
LIBFT = $(LIBFTPATH)/libft.a
LIBMALLOC = ft_malloc_$(HOSTTYPE)

##### INCLUDE #####
PATH_INCLUDE = $(SRCPATH)/includes
PATH_INCLUDE2 = ./libft
HEADERS = $(PATH_INCLUDE)/*.h
HEADERS2 = $(PATH_INCLUDE2)/*.h
INC = $(addprefix -I , $(PATH_INCLUDE) $(PATH_INCLUDE2))


##### COMPILER #####
CC = clang
CCFLAGS = -Wall -Werror -Wextra -fPIC -fvisibility=hidden

##### OSTYPE #####
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	# mac
	CCFLAGS += -D DARWIN
else
	#Linux and others...
	CCFLAGS += -D LINUX
endif

##### SRCS #####
SRCS = $(addprefix $(SRCPATH)/, malloc.c free.c realloc.c shared.c show_alloc_mem.c)
OBJ = $(SRCS:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

### BUILD ###

all : mk_objdir $(NAME) #tester

mk_objdir:
	@if [ ! -d $(OBJPATH) ]; then mkdir $(OBJPATH); fi

# tester:
# 	gcc -o malloc_tester malloc_tester.c -L. -lft_malloc

$(NAME): $(LIBFT) $(OBJ)
	@echo "\n$(END)$(BLUE)# Making $(NAME) #$(END)$(GREY)"
	$(CC) -shared -o $@ $(OBJ) $(LIBFT)
	@ln -sf $@ $(L_NAME)
	@echo "\n$(END)$(GREEN)# $(NAME) is built #$(END)"

$(LIBFT): 
	@make -C $(LIBFTPATH)

$(OBJPATH)/%.o : $(SRCPATH)/%.c $(HEADERS)
	$(CC) $(CCFLAGS) $(INC) -c $< -o $@

### CLEAN ###

clean :
	@echo "$(END)$(RED)# removing $(NAME) objects #$(END)$(GREY)"
	@rm -rf $(OBJ)
	@make clean -C $(LIBFTPATH)
	# @rm malloc_tester

fclean : clean
	@echo "$(END)$(RED)\n# removing $(NAME) #$(END)$(GREY)"
	@rm -f $(NAME)
	@rm -f $(L_NAME)
	@make fclean -C $(LIBFTPATH)

re : fclean
	@$(MAKE)

.PHONY : all clean fclean re