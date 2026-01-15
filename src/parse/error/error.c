# include "../../../includes/minishell.h"

void    ps_error(char *msg)
{
    write(1, msg, ft_strlen(msg));
}

void    basic_error(char *msg)
{
    if (!ft_strcmp(MALLOC_FAIL, msg))
        te()->exit_code = 1;
    write(1, msg, ft_strlen(msg));
    exit(1);
}