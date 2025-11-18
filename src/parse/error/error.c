#include "../../../includes/minishell.h"

void	ps_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	basic_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(0);
}
