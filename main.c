#include "includes/minishell.h"

t_env  *te()
{
    static t_env env;
    return (&env);
}

int main(int argc, char **argv, char **envp)
{
    pipeline_from_cli(argc, argv);
    mount_envp(envp);
    for(int i = 0; te()->envp[i]; i++)
        printf("%s\n", te()->envp[i]);
    buitin_cd(argv[2]);
    printf("\n\n");
    for(int i = 0; te()->envp[i]; i++)
        printf("%s\n", te()->envp[i]);
    printf("oldpwd: %s\n", te()->oldpwd);
    built_echo(argv[2]);
    built_pwd();
    return (0);
}