# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achansar <achansar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 15:07:40 by achansar          #+#    #+#              #
#    Updated: 2022/10/17 14:48:57 by achansar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit \
	  ft_isprint ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset \
	  ft_split ft_strchr ft_strdup ft_strjoin ft_strlcat ft_strlcpy ft_strlen \
	  ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr ft_tolower \
	  ft_toupper ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd \
	  ft_putendl_fd ft_putnbr_fd

SRC_BONUS = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstadd_back_bonus \
			ft_lstsize_bonus ft_lstlast_bonus ft_lstdelone_bonus \
			ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

OBJ = $(SRC:=.o)
OBJ_BONUS = $(SRC_BONUS:=.o)
CFILES = $(SRC:=.c)
CFILES_BONUS = $(SRC_BONUS:=.c)
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

.c.o:
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
