# include "../../includes/minishell.h"

int verifications_after_malloc_struct(t_tokens *t)
{
    ps()->tl = tok_split(t);
    add_to_struct();
    add_cmd_argv(ps()->tl);
    return (1);
}
