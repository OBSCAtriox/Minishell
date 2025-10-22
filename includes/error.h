#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

# define ERR_ARG BFGRED "Error\n"RESET
# define SYNT_ERR BFGRED "bash: syntax error near unexpected token ´|'\n"RESET
# define MALLOC_FAIL BFGRED "Malloc Failure.\n"RESET

void	basic_error(char *msg);

#endif