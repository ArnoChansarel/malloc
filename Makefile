#TARGET
NAME = malloc

#ARGUMENTS
CC = gcc
FLAGS = #-Wall -Werror -Wextra
SEG = #-fsanitize=address -g

#Files
SRC_PATH = ./srcs/
SRC =	malloc
C_FILES = $(addprefix $(SRC_PATH), $(SRC:=.c))
OBJ = $(addprefix $(SRC_PATH), $(SRC:=.o))

#LIBFT
# LBFT_PATH = ./libft/
# LBFT =		ft_bzero \
# 			ft_memset \
# 			ft_strlen \
# 			ft_strdup
# LBFT_FILES = $(addprefix $(LBFT_PATH), $(LBFT:=.c))
# LBFT_OBJ = $(addprefix $(LBFT_PATH), $(LBFT:=.o))

#RULES
all: $(NAME)

$(NAME): $(OBJ) $(LBFT_OBJ)
	@ $(CC) $(FLAGS) $(SEG) $(OBJ) -o $(NAME)

.c.o:
	@ $(CC) $(FLAGS) $(SEG) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re