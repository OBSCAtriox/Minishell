#include "../../includes/minishell.h"

/* void    count_cmd(void)
{
    int i;

    i = 0;
    while(tp()->cmdv[i])
        i++;
    tc()->num_cmd = i;
}

int    count_redir(t_cmd *cmdv)
{
    int i;

    i = 0;
    while(cmdv->redir[i])
        i++;
    return (i);
} */
int count_var(char *line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(line[i])
    {
        if(line[i] == '$' && (line[i + 1] == '_' || line[i + 1] == '?' || ft_isalpha(line[i + 1])))
            count++;
        i++;
    }
    return (count);
}

void    free_str(void *p1)
{
    if(p1)
        free(p1);
}

int len_expanded_var(char *line)
{
    t_data dt;

    dt.result = 0;
    dt.size = count_var(line);
    dt.var = exp_str_var(line);
    if(!dt.var)
        return (0);
    dt.i = 0;
    while(dt.i < dt.size)
        dt.result += ft_strlen(dt.var[dt.i++]);
    free_doble_pointer(dt.var);
    return (dt.result);
}

int is_valid_character(char c)
{
    if(c == '_' || c == '?' || ft_isalnum(c))
        return (TRUE);
    return (FALSE);
}

void inits_expand_line(t_data *dt, char *line, char ***exp)
{
    dt->i = 0;
    dt->j = 0;
    dt->k = 0;
    dt->len = count_len_exp(line);
    *exp = exp_str_var(line);
}
