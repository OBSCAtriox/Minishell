# include "../../includes/minishell.h"

void     num_pipes(const char *line)
{
    int n;
    bool    quote;
    bool    d_quote;

    d_quote = false;
    quote = false;
    n = 0;
    while (*line)
    {
        if (*line == '\'' && !d_quote)
            quote = !quote;
        else if (*line == '"' && !quote)
            d_quote = !d_quote;
        else if (*line == '|' && quote == false && d_quote == false)
            n++;
        line++;
    }
    ps()->n_cmd = n + 1;
    ps()->n_pipes = n;
}

int   pipe_ver_start(const char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if (ms_isspaces(line[i]))
            i++;
        else
        {
            if (line[i] == '|')
                return (0);
            break;
        }
    }
    return (1);
}

int    pipe_ver_end(const char *line)
{
    size_t lenght;

    lenght = ft_strlen(line) - 1;
    while (line[lenght])
    {
        if (ms_isspaces(line[lenght]))
            lenght--;
        else
        {
            if (line[lenght] == '|')
                return (0);
            break ;
        }
    }
    return (1);
}

int    pipe_ver_mid(const char *line)
{
    int i;
    int y;
    bool ver;

    i = 0;
    y = 0;
    ver = false;
    while (line[i])
    {
        if (line[i] == '|' && !ver)
        {
            y = i + 1;
            ver = true;
            i++;
        }
        if (line[i] == '|')
        {
            if (!pipe_ver_mid_help(line, i, y))
                return (0);
        }
        i++;
    }
    return (1);
}

int     pipe_ver_mid_help(const char *line, int i, int y)
{
    if (i - y == 1)
        return (0);
    while (y != i)
    {
        if (!ms_isspaces(line[y]))
            return (1);
        y++;
    }
    return (0);
}
