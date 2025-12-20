#include "../../../includes/minishell.h"

void    cleanup(void)
{
    if (te()->envp)
    {
        free_doble_pointer(te()->envp);
        te()->envp = NULL;
    }
    if (te()->l_var)
    {
        free_doble_pointer(te()->l_var);
        te()->l_var = NULL;
    }
    if (te()->oldpwd)
    {
        free(te()->oldpwd);
        te()->oldpwd = NULL;
    }
    if(te()->var_exp)
        free_doble_pointer(te()->var_exp);
    free_all("", 0);
    free_pipeline();
}

void    free_doble_pointer(char **p)
{
    int i;

    if(!p)
        return ;
    i = 0;
    while(p[i])
    {
        free(p[i]);
        i++;
    }
    free(p);
    p = NULL;
}

void    free_vetor_failed(char **vetor, int i)
{
    int j;

    if(!vetor)
        return ;
    j = 0;
    while(j < i)
    {
        free(vetor[j]);
        j++;
    }
    free(vetor);
}

void    clean_redir(t_redir **redir)
{
    int i;

    if(!redir)
        return ;
    i = 0;
    while(redir[i])
    {
        if(redir[i]->path)
            free(redir[i]->path);
        if(redir[i]->hdoc_fd != -1)
            close(redir[i]->hdoc_fd);
        free(redir[i]);
        i++;
    }
    free(redir);
}

void    free_pipeline(void)
{
    t_cmd **cmdv;
    t_redir **redir;
    int i;

    cmdv = ms()->cmdv;
    if(!cmdv)
        return;
    i = 0;
    while (cmdv[i])
    {
        free_doble_pointer(cmdv[i]->argv);
        redir = cmdv[i]->redir;
        if (redir)
            clean_redir(redir);
        free(cmdv[i]);
        i++;
    }
    free_doble_pointer(tc()->paths);
    free(cmdv);
    ms()->cmdv = NULL;
}
