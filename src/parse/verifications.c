# include "../../includes/minishell.h"

int    verifications(const char *line)
{
        num_pipes(line);
        if (!pipe_ver_end(line)
        || !pipe_ver_start(line)
        || !pipe_ver_mid(line))
        {
            ps_error(SYNT_ERR);
            return (0);
        }
        malloc_struct();
    return (1);
}
