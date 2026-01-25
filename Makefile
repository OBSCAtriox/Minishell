include includes/colors.mk

CC = cc
FLAGS = -Wall -Werror -Wextra

NAME = minishell

FLAGS_VAL = --leak-check=full --trace-children=yes --track-fds=yes --suppressions=valgrind_readline.supp

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline -lhistory

SRC = main.c src/parse/pipeparse.c src/parse/utils/isspaces.c \
src/parse/error/error.c src/parse/utils/init.c src/parse/verifications.c \
src/parse/mallocs/struct_mallocs.c src/parse/free_funcs/free_ver1.c \
src/parse/tokens/tokens.c src/parse/tokens/tokens_utils.c \
src/parse/redir/redir_ver_target.c src/parse/redir/redir_utils.c \
src/parse/tokens/tokens_ver.c src/parse/quote_split/ms_split.c  \
src/parse/quote_split/ms_split_list.c src/parse/add_to_struct/add_to_struct.c \
src/parse/add_to_struct/ver_tok_list_utils.c src/parse/add_to_struct/ver_tok_list.c \
src/parse/token_split/tok_split.c src/parse/verifications_after_malloc_struct.c \
src/parse/free_funcs/free_ver2.c src/parse/utils/isspaces_split.c src/parse/tokens/tokens_utils2.c \
\
src/env/set_env.c src/env/utils_env_1.c src/exec/builtin/cd.c src/exec/builtin/echo.c \
src/exec/error/error_msg.c src/exec/builtin/pwd.c src/env/utils_env_2.c src/exec/utils/utils_export.c \
src/exec/builtin/export.c src/env/utils_env_3.c src/exec/builtin/unset.c src/exec/builtin/env.c \
src/exec/utils/free.c src/exec/builtin/exit.c src/heredoc/utils.c src/heredoc/expand.c \
src/heredoc/utils_2.c src/heredoc/heredoc.c src/exec/execution.c src/exec/utils/utils_execution.c \
src/exec/redir/redir.c src/exec/path/find_path.c src/exec/utils/utils_execution_2.c \
src/exec/utils/utils_execution_3.c src/exec/redir/utils.c src/exec/utils/handler_signal.c\
src/env/set_var_exp.c src/exec/utils/utils_execution_4.c src/exec/utils/utils_export_2.c\
src/exec/utils/free_2.c src/exec/utils/utils_execution_5.c src/heredoc/utils_3.c\
src/utils_main.c src/utils_main_2.c src/exec/utils/utils_execution_6.c src/exec/utils/utils_exit.c\
src/exec/error/set_error.c src/exec/utils/utils_cd.c src/exec/utils/utils_execution_7.c\

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo -e "$(FGGREEN)"
	$(CC) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
	@echo -e "$(RESET)"
	@echo -e "😎$(FGGREEN)Minishell Creation Sucessfull$(RESET)😎\n"
	@echo -e "$(FGCYAN)"
	@cat T_shell.txt
	@echo -e "$(RESET)"
	@echo -e "                                       $(BLINKS)🫡$(BOLD)$(ITALIC)$(BFGCYAN) T_shell Ready to GO 🫡$(RESET)"
	@echo

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus
	@echo -e "📚$(FGCYAN)Libft Compilation Sucessfull$(RESET)📚"

%.o: %.c
	@echo -e "✨$(FGYELLOW)Object Compilation Sucessfull✨"
	$(CC) $(FLAGS) -c $< -o $@
	@echo -e "$(RESET)"

val:
	valgrind $(FLAGS_VAL) ./$(NAME)

clean:
	rm -f $(OBJ)
	@echo -e "$(FGRED)"
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo -e "$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo -e "$(FGRED)"
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo -e "$(RESET)"

re: fclean all

.PHONY: all clean fclean re
