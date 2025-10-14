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
        num_pipes(line);
        pipe_ver_start(line);
        pipe_ver_end(line);
        pipe_ver_mid(line);
        free(line);
    }   
}
