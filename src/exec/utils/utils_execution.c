#include "../../../includes/minishell.h"

static int  is_builtin(const char *command, const char *name)
{
    size_t  cmd_len;
    size_t  name_len;

    if (!command || !name)
        return (0);
    cmd_len = ft_strlen(command);
    name_len = ft_strlen(name);
    if (cmd_len != name_len)
        return (0);
    return (ft_strncmp(command, name, name_len) == 0);
}

void    call_builtin(char **arg)
{
    char *command;

    if (!arg || !arg[0])
        return ;
    command = arg[0];
    if (is_builtin(command, "echo"))
        builtin_echo(arg[1]);
    else if (is_builtin(command, "cd"))
        builtin_cd(arg);
    else if (is_builtin(command, "env"))
        builtin_env();
    else if (is_builtin(command, "pwd"))
        builtin_pwd();
    else if (is_builtin(command, "unset"))
        builtin_unset(arg);
    else if (is_builtin(command, "export"))
        builtin_export(arg);
    else if (is_builtin(command, "exit"))
        builtin_exit(arg);
    else
        print_error(command, "comand not found");
}

int clone_std(void)
{
    tc()->fd_stdin = dup(STDIN_FILENO);
    if(tc()->fd_stdin < 0)
    {
        perror("dup-in");
        return (FALSE);
    }
    tc()->fd_stdout = dup(STDOUT_FILENO);
    if(tc()->fd_stdout < 0)
    {
        perror("dup-out");
        return (FALSE);
    }
    return (TRUE);
}

int restore_std(void)
{
    int std_in;
    int std_out;

    std_in = tc()->fd_stdin;
    std_out = tc()->fd_stdout;
    if(std_in >= 0)
    {
        if (dup2(std_in, STDIN_FILENO) < 0)
            return (perror("dup2-in"), FALSE);
        close(tc()->fd_stdin);
        tc()->fd_stdin = -1;
    }
    if(std_out >= 0)
    {
        if(dup2(std_out, STDOUT_FILENO) < 0)
            return (perror("dup2-out"), FALSE);
        close(tc()->fd_stdout);
        tc()->fd_stdout = -1;
    }
    return (TRUE);
}

void    count_cmd(void)
{
    int i;

    i = 0;
    while(ms()->cmdv[i])
        i++;
    tc()->num_cmd = i;
}