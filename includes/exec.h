#ifndef EXEC_H
#define EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>

#define FALSE 0
#define TRUE 1

typedef struct s_data
{
    int     result;
    int     count;
    int     index;
    int     size;
    int     len;
    char    *str;
    char    *temp;
    char    **env;
    char    **var;
    int     *index_p;
    int     *len_p;
    int     i;
    int     j;
    int     k;
    int     l;
}           t_data;

typedef struct s_control
{
    int num_cmd;
    int num_redr;
    int signaled_heredoc;
}       t_control;

t_control   *tc(void);
int size_vetor(char **vetor);
int    mount_envp(char **envp);
void    free_vetor_failed(char **vetor, int i);
int buitin_cd(char **argv);
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
int is_valid_identifier(char *arg);
char    *get_name_var(char *arg);
char    *get_value_var(char *arg);
int has_equal(char *arg);
void    export_variable(char *arg);
int    re_mount_locar_var(char **envp);
int    create_new_local_var(char *name, char *value);
int remove_env_var(int index);
int builtin_unset(char  *arg);
int    skip_var_dell(int index, int *i);
int remove_local_var(int index);
void builtin_env(void);
void    builtin_exit(char **arg);
void    free_all(void);
int ft_isnumeric(char *str);
char    *get_target(char **arg);
void    free_cd(char **new_pwd, char **target, char **old_pwd, int err);
void    exp_find_var(char *line, int **index, int **len);
int count_var(char *line);
char    **exp_str_var(char *line);
int count_len_exp(char *line);
void    free_str(void *p1);
int len_expanded_var(char *line);
char    *expand_line(char *line);
int is_valid_character(char c);
void inits_expand_line(t_data *dt, char *line, char ***exp);
void    initis_exp_find_var(t_data *dt, char *line);
void    free_expand_line(t_data *dt, char ***exp);
void    heredoc(void);
int    mount_heredoc(int idx_cmd, int idx_rdir);
void    read_heredoc(int idx_cmd, int idx_rdir, int *fd, char *delim);
void    write_line(int quoted, char *line, int fd);
void wait_heredoc(pid_t pid);
void    close_fd_redir(void);

#endif