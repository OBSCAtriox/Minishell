# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiago <tiago@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 18:08:12 by thde-sou          #+#    #+#              #
#    Updated: 2025/11/27 16:09:58 by tiago            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = libft.a

MARKER = .lib_bonus_created

MAIN = main.c

EXEC = a.out

SANITIZE = -g -fsanitize=address,undefined,leak -O1

SRC = ft_atoi.c ft_isprint.c  ft_putchar_fd.c  ft_striteri.c  ft_strnstr.c \
ft_bzero.c    ft_itoa.c     ft_putendl_fd.c  ft_strjoin.c   ft_strrchr.c \
ft_calloc.c   ft_memchr.c   ft_putnbr_fd.c   ft_strlcat.c   ft_strtrim.c \
ft_isalnum.c  ft_memcmp.c   ft_putstr_fd.c   ft_strlcpy.c   ft_substr.c \
ft_isalpha.c  ft_memcpy.c   ft_split.c       ft_strlen.c    ft_tolower.c \
ft_isascii.c  ft_memmove.c  ft_strchr.c      ft_strmapi.c   ft_toupper.c \
ft_isdigit.c  ft_memset.c   ft_strdup.c      ft_strncmp.c	ft_itoa_base.c \
get_next_line.c get_next_line_utils.c ft_strcmp.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:_bonus.c=_bonus.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJ_BONUS) $(MARKER)

$(MARKER) : $(OBJ) $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)
	touch $(MARKER)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

run: $(NAME) $(MAIN)
	$(CC) $(MAIN) $(NAME)
	./$(EXEC)

leak: $(NAME) $(MAIN)
	$(CC) $(SANITIZE) $(MAIN) $(NAME)
	./$(EXEC)

clean:
	rm -f $(OBJ) $(OBJ_BONUS) $(MARKER)
	rm -f $(EXEC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re run leak
