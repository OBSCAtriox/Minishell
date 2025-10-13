#ifndef EXEC_H
#define EXEC_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct s_data
{
    int     index;
    int     size;
    int     len;
    char    *str;
    char    **env;
}           t_data;

int size_vetor(char **vetor);
int    mount_envp(char **envp);
void    free_vetor_failed(char **vetor, int i);
int buitin_cd(char *argv);
int find_variable(char *name);
char    *join3(char *s1, char *s2, char *s3);
void    free_doble_pointer(char **p);
int    add_variable(char *name, char *value);
int env_set(char *name, char *value);
void    print_error(char *msg);
void    error_cd(char *arg);
void    built_echo(char *arg);
void    built_pwd(void);
void    error_pwd(void);

#endif