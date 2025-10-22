CC = cc
FLAGS = -Wall -Werror -Wextra

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READ_LINE = -lreadline

SRC = main.c \
src/env/set_env.c src/env/utils_env_1.c src/exec/builtin/cd.c src/exec/builtin/echo.c \
src/exec/error/error_msg.c src/exec/builtin/pwd.c src/env/utils_env_2.c src/exec/utils/utils_export.c \
src/exec/builtin/export.c src/env/utils_env_3.c src/exec/builtin/unset.c src/exec/builtin/env.c \
src/exec/utils/free.c src/exec/builtin/exit.c src/heredoc/utils.c src/heredoc/expand.c \
src/heredoc/utils_2.c src/heredoc/heredoc.c src/exec/execution.c src/exec/utils/utils_execution.c \
src/exec/redir/redir.c src/exec/path/find_path.c src/exec/utils/utils_execution_2.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(READ_LINE) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re