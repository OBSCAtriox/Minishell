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
    int     i;
    int     j;
    char    *str;
    char    *temp;
    char    **env;
}           t_data;

int size_vetor(char **vetor);
int    mount_envp(char **envp);
void    free_vetor_failed(char **vetor, int i);
int buitin_cd(char *argv);
int find_variable(char *name, char **env);
char    *join3(char *s1, char *s2, char *s3);
void    free_doble_pointer(char **p);
int    update_variable(char *name, char *value, char **env);
int env_set(char *name, char *value, char **env);
void    print_error(char *msg);
void    error_cd(char *arg);
void    built_echo(char *arg);
void    built_pwd(void);
void    error_pwd(void);
char    *expand_variable(char *name, char **env);
void    print_export(void);
int find_next_min(char **env, int *printed);
int ft_strcmp_var(const char *s1, const char *s2);
void    print_export_line(char *env);
void    builtin_export(char *argv);
void    create_local_variable(char *name, char *value);
int is_valid_indentifier(char *arg);
char    *get_name_var(char *arg);
char    *get_value_var(char *arg);
int has_equal(char *arg);
void    export_variable(char *arg);

#endif