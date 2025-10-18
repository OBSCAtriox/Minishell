#include "../../includes/minishell.h"

char    *expand_line(char *line)
{
    t_data dt;
    char    **exp;
    char    *line_out;

    dt.i = 0;
    dt.j = 0;
    dt.k = 0;
    exp = exp_str_var(line);
    dt.len = count_len_exp(line);
    exp_find_var(line, &dt.index_p, &dt.len_p);
    line_out = malloc(sizeof(char) * (dt.len + 1));
    if(!exp || !line_out)
        return (NULL);
    while(dt.i < dt.len)
    {
        dt.l = 0;
        if(line[dt.j] == '$' && (line[dt.j + 1] == '_' || line[dt.j + 1] == '?' || ft_isalnum(line[dt.j + 1])))
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
    return (line_out);
}

void    exp_find_var(char *line, int **index, int **len)
{
    int i;
    int k;
    int j;
    int count;

    count = count_var(line);
    *index = malloc(sizeof(int) * count);
    *len = malloc(sizeof(int) * count);
    if(!*index || !*len)
        return;
    i = 0;
    k = 0;
    while(line[i])
    {
        j = 1;
        if(line[i] == '$' && (line[i + 1] == '_' || line[i + 1] == '?' || ft_isalnum(line[i + 1])))
        {
            (*index)[k] = i + 1;
            while (line[i + j] && (ft_isalnum(line[i + j]) || line[i + j] == '?' || line[i + j] == '_'))
            {
                j++;
                if(line[i + 1] == '?')
                    break;
            }
            (*len)[k] = j - 1;
            k++;
        }
        i++;
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
        if(line[dt.i] == '$' && (line[dt.i + 1] == '_' || line[dt.i + 1] == '?' || ft_isalnum(line[dt.i + 1])))
        {
            while(line[dt.i + dt.j] && (ft_isalnum(line[dt.i + dt.j]) || line[dt.i + dt.j] == '?' || line[dt.i + dt.j] == '_'))
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
