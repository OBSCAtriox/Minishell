CC = cc
FLAGS = -Wall -Werror -Wextra

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline -lhistory

SRC = main.c src/parse/pipeparse.c src/parse/utils/isspaces.c \
src/parse/error/error.c src/parse/utils/init.c src/parse/verifications.c \
src/parse/mallocs/struct_mallocs.c src/parse/free_funcs/free_ver1.c \
src/parse/tokens/tokens.c src/parse/tokens/tokens_utils.c \
src/parse/redir/redir_ver_target.c src/parse/redir/redir_utils.c \
src/parse/tokens/tokens_ver.c src/parse/quote_split/ms_split.c  \
src/parse/quote_split/ms_split_list.c \
\
src/env/set_env.c src/env/utils_env_1.c src/exec/builtin/cd.c src/exec/builtin/echo.c \
src/exec/error/error_msg.c src/exec/builtin/pwd.c src/env/utils_env_2.c src/exec/utils/utils_export.c \
src/exec/builtin/export.c src/env/utils_env_3.c src/exec/builtin/unset.c src/exec/builtin/env.c \
src/exec/utils/free.c src/exec/builtin/exit.c src/heredoc/utils.c src/heredoc/expand.c \
src/heredoc/utils_2.c src/heredoc/heredoc.c src/exec/execution.c src/exec/utils/utils_execution.c \
src/exec/redir/redir.c src/exec/path/find_path.c src/exec/utils/utils_execution_2.c \
src/exec/utils/utils_execution_3.c src/exec/redir/utils.c \

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

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