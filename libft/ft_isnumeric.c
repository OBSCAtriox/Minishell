#include "libft.h"

int ft_isnumeric(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while(str[i])
    {
        if (str[i] < 48 || str[i] > 57)
            return (0);
        i++;
    }
    return (1);
}