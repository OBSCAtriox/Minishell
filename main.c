#include "includes/minishell.h"

t_env  *te()
{
    static t_env env;
    return (&env);
}

t_pipeline  *ms()
{
    static t_pipeline ms;
    return (&ms);
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    (void)argv;
    if (argc != 1)
        basic_error(ERR_ARG);
    mount_envp(envp);
    while(1)
    {
        line = readline("T_Shell>");
        verifications(line);
        free(line);
    }   
}
