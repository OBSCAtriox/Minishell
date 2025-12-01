#include "../../includes/minishell.h"

char    *expand_line(char *line)
{
    t_data dt;
    char    **exp;
    char    *line_out;

    inits_expand_line(&dt, line, &exp);
    exp_find_var(line, &dt.index_p, &dt.len_p);
    line_out = malloc(sizeof(char) * (dt.len + 1));
    if(!exp || !line_out)
        return (NULL);
    while(dt.i < dt.len)
    {
        dt.l = 0;
        if(line[dt.j] == '$' && is_valid_character(line[dt.j + 1]))
        {
            while(exp[dt.k][dt.l])
                line_out[dt.i++] = exp[dt.k][dt.l++];
            dt.j += dt.len_p[dt.k] + 1;
            dt.k++;
        }
        else
            line_out[dt.i++] = line[dt.j++];
    }
    line_out[dt.len] = '\0';
    free_expand_line(&dt, &exp);
    return (line_out);
}

void    exp_find_var(char *line, int **index, int **len)
{
    t_data dt;

    initis_exp_find_var(&dt, line);
    *index = malloc(sizeof(int) * dt.count);
    *len = malloc(sizeof(int) * dt.count);
    if(!*index || !*len)
        return;
    while(line[dt.i])
    {
        dt.j = 1;
        if(line[dt.i] == '$' && is_valid_character(line[dt.i + 1]))
        {
            (*index)[dt.k] = dt.i + 1;
            while (line[dt.i + dt.j] && is_valid_character(line[dt.i + dt.j]))
            {
                dt.j++;
                if(line[dt.i + 1] == '?')
                    break;
            }
            (*len)[dt.k] = dt.j - 1;
            dt.k++;
        }
        dt.i++;
    }
}

char    **exp_str_var(char *line)
{
    t_data dt;

    dt.size = count_var(line);
    exp_find_var(line, &dt.index_p, &dt.len_p);
    dt.var = malloc(sizeof(char *) * (dt.size + 1));
    if(!dt.var || !dt.index_p || !dt.len_p)
        return (NULL);
    dt.i = 0;
    while(dt.i < dt.size)
    {
        dt.str = ft_substr(line, dt.index_p[dt.i], dt.len_p[dt.i]);
        if(dt.str[0] == '?')
        {
            dt.var[dt.i++] = ft_itoa(te()->exit_code);
            free(dt.str);
            continue;
        }
        dt.var[dt.i] = expand_variable(dt.str, te()->envp);
        if(!dt.var[dt.i])
            dt.var[dt.i] = ft_strdup("");
        free_str(dt.str);
        dt.i++;
    }
    dt.var[dt.size] = NULL;
    return(free(dt.index_p), free(dt.len_p), dt.var);
}

int count_len_exp(char *line)
{
    t_data dt;

    dt.i = 0;
    dt.size = 0;
    dt.result = 0;
    while(line[dt.i])
    {
        dt.j = 1;
        if(line[dt.i] == '$' && is_valid_character(line[dt.i + 1]))
        {
            while(line[dt.i + dt.j] && is_valid_character(line[dt.i + dt.j]))
            {
                if(line[dt.i + dt.j] == '?')
                {
                    dt.j = 2;
                    break;
                }
                dt.j++;
            }
            dt.size += dt.j;
        }
        dt.i++;
    }
    dt.result = len_expanded_var(line);
    return (ft_strlen(line) - dt.size + dt.result);
}
