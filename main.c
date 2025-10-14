#include "includes/minishell.h"

t_env  *te()
{
    static t_env env;
    return (&env);
}

int main(int argc, char **argv, char **envp)
{
    if(argc < 2)
        return (0);
    mount_envp(envp);
    create_local_variable("XXX", "thiago");
    /* for(int i = 0; te()->envp[i]; i++)
        printf("%s\n", te()->envp[i]); */
    printf("\n\n");
    //printf("oldpwd: %s\n", te()->oldpwd);
    //built_echo(argv[2]);
    built_pwd();
    buitin_cd(argv[2]);
    built_pwd();
    //printf("%s\n", get_value_var("_var=thiago"));
    builtin_export(argv[2]);
    for(int i = 0; te()->envp[i]; i++)
        printf("%s\n", te()->envp[i]);
    /* for(int i = 0; te()->l_var[i]; i++)
        printf("%s\n", te()->l_var[i]); */
    free_doble_pointer(te()->envp);
    if(te()->oldpwd)
        free(te()->oldpwd);
    return (0);
}