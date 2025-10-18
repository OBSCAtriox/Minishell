#include "../../includes/minishell.h"

void    initis_exp_find_var(t_data *dt, char *line)
{
    dt->i = 0;
    dt->k = 0;
    dt->count = count_var(line);
}

void    free_expand_line(t_data *dt, char ***exp)
{
    if(dt->len_p)
        free(dt->len_p);
    if(dt->index_p)
        free(dt->index_p);
    if(*exp)
        free(*exp);
}
