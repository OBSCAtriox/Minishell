CC = cc
FLAGS = -Wall -Werror -Wextra

NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline -lhistory

SRC = src/exec/builtin/cd.c src/exec/builtin/echo.c src/exec/builtin/pwd.c \
src/exec/error/error_msg.c src/env/set_env.c \
main.c src/env/utils_env.c src/parse/pipeparse.c src/parse/utils/isspaces.c \
src/parse/error/error.c src/parse/utils/init.c src/parse/verifications.c \
src/parse/mallocs/struct_mallocs.c src/parse/free_funcs/free_ver1.c \
src/parse/tokens/tokens.c src/parse/tokens/tokens_utils.c \
src/parse/redir/redir_ver_target.c src/parse/redir/redir_utils.c \

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