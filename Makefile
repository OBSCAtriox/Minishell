# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 17:27:45 by thde-sou          #+#    #+#              #
#    Updated: 2025/10/12 18:43:14 by thde-sou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = pipeline_from_cli.c main.c \
src/set_env.c src/utils/utils_env.c src/builtin/cd.c src/builtin/echo.c \
src/error/error_msg.c src/builtin/pwd.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

race: $(OBJ)
	$(CC) $(FLAG_THREAD) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re