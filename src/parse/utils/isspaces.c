# include "../../../includes/minishell.h"

int     ms_isspaces(char c)
{
    if ((c >= 9 && c <= 13) || c == ' ')
        return (1);
    return (0);
}
