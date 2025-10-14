# include "../../includes/minishell.h"

void    quote_ver(char *line)
{
    int i;

    i = 0;
    ps()->ver.tf = false;
    while (line[i] != '|' || line[i] != '\0')
    {
        
    }

}

void    line_ver(char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0' || line[i] != '|')
    {
        if (ft_isalpha(line[i]))
        {

        }
    }
}