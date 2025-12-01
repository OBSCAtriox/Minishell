#include "../../../includes/minishell.h"

int is_dir(char *arg)
{
    struct stat info;

    if (stat(arg, &info) == 0)
    {
	    if (S_ISDIR(info.st_mode))
            return (TRUE);
    }
    return (FALSE);
}

int check_path(char *arg)
{
    if(is_dir(arg))
    {
        print_error(arg, "Is a directory");
        tc()->exit_path = 126;
        return (FALSE);
    }
    else
    {
        if(access(arg, X_OK) < 0)
        {
            print_error(arg, "No such file or directory");
            tc()->exit_path = 127;
            return (FALSE);
        }
    }
    return (TRUE);
}

/* int safe_open_read(char *path)
{
    int fd;

    if(access(path, F_OK) == 0)
    {
        if(access(path, R_OK) == 0)
            fd = open(path, O_RDONLY);
        else
        {
            print_error(path, "Permission denied");
            tc()->exit_path = 126;
        }
    }
    else
    {
        print_error(path, "No such file or directory");
        tc()->exit_path = 127;
    }
    return (fd);
} */
