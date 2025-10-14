#include "../../includes/minishell.h"

static int	is_builtin_name(const char *name);
static t_redir_type redir_type_from_token(const char *token);
static t_redir	*redir_new(t_redir_type type, const char *token);
static int	redir_append(t_redir **list, t_redir *node);
static void	destroy_pipeline(t_pipeline *pipeline);

t_pipeline	*pipeline_from_cli(int argc, char **argv)
{
    t_pipeline *pipeline;
    t_cmd      *cmd;
    int         i;
    int         acmd;

    pipeline = calloc(1, sizeof(*pipeline));
    if (!pipeline)
        return (NULL);
    if (argc <= 1)
        return (pipeline);
    pipeline->cmdv = calloc(2, sizeof(t_cmd *));
    if (!pipeline->cmdv)
        goto fail;
    cmd = calloc(1, sizeof(*cmd));
    if (!cmd)
        goto fail;
    pipeline->cmdv[0] = cmd;
    cmd->argv = calloc(argc, sizeof(char *));
    if (!cmd->argv)
        goto fail;
    i = 1;
    acmd = 0;
    while (i < argc)
    {
        char *tok;

        tok = argv[i];
        if (!strcmp(tok, "<") || !strcmp(tok, ">") || !strcmp(tok, ">>")
            || !strcmp(tok, "<<"))
        {
            t_redir     *redir;
            t_redir_type type;

            if (++i >= argc)
                goto fail;
            type = redir_type_from_token(tok);
            redir = redir_new(type, argv[i]);
            if (redir_append(&cmd->redir, redir))
                goto fail;
        }
        else
        {
            cmd->argv[acmd] = strdup(tok);
            if (!cmd->argv[acmd])
                goto fail;
            acmd++;
        }
        i++;
    }
    cmd->argv[acmd] = NULL;
    cmd->is_builtin = is_builtin_name(cmd->argv[0]);
    return (pipeline);
fail:
    destroy_pipeline(pipeline);
    return (NULL);
}

static int	is_builtin_name(const char *name)
{
    if (!name)
        return (0);
    return (!strcmp(name, "echo")
        || !strcmp(name, "cd")
        || !strcmp(name, "pwd")
        || !strcmp(name, "export")
        || !strcmp(name, "unset")
        || !strcmp(name, "env")
        || !strcmp(name, "exit"));
}

static t_redir_type redir_type_from_token(const char *token)
{
    if (!strcmp(token, "<"))
        return (R_IN);
    if (!strcmp(token, ">"))
        return (R_OUT);
    if (!strcmp(token, ">>"))
        return (R_APP);
    return (R_HDOC);
}

static t_redir *redir_new(t_redir_type type, const char *token)
{
    t_redir *node;

    node = calloc(1, sizeof(*node));
    if (!node)
        return (NULL);
    node->type = type;
    node->fd_target = (type == R_IN || type == R_HDOC) ? 0 : 1;
    if (token)
    {
        node->path = strdup(token);
        if (!node->path)
        {
            free(node);
            return (NULL);
        }
    }
    node->hdoc_fd = -1;
    return (node);
}

static int redir_append(t_redir **list, t_redir *node)
{
    t_redir *it;

    if (!node)
        return (-1);
    if (!*list)
    {
        *list = node;
        return (0);
    }
    it = *list;
    while (it->next)
        it = it->next;
    it->next = node;
    return (0);
}

static void destroy_pipeline(t_pipeline *pipeline)
{
    t_redir *redir;
    t_cmd   *cmd;
    int      i;

    if (!pipeline)
        return;
    if (pipeline->cmdv)
    {
        i = 0;
        while ((cmd = pipeline->cmdv[i++]))
        {
            if (cmd->argv)
            {
                int j;

                j = 0;
                while (cmd->argv[j])
                {
                    free(cmd->argv[j]);
                    j++;
                }
                free(cmd->argv);
            }
            while ((redir = cmd->redir))
            {
                cmd->redir = redir->next;
                free(redir->path);
                free(redir->hdoc_tmp);
                free(redir);
            }
            free(cmd);
        }
        free(pipeline->cmdv);
    }
    free(pipeline);
}
