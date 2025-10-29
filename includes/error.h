#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

# define ERR_ARG BFGRED "T_Shell: Error\n" RESET
# define SYNT_ERR_P BFGRED "T_Shell: syntax error near unexpected token --> ´|'\n" RESET
# define SYNT_ERR_R BFGRED "T_Shell: syntax error from --> ´redirections'\n" RESET
# define MALLOC_FAIL BFGRED "T_Shell: Malloc Failure.\n" RESET
# define UNCLOSED_QUOTES BFGRED "T_Shell: syntax error from --> ´Unclosed Quotes'\n" RESET
void	basic_error(char *msg);

#endif