# ifndef PARSING_H
# define PARSING_H

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_line_ver
{
    char    quote;
    bool    tf;
} t_line_ver;

typedef struct s_parse
{
    t_line_ver ver;
    char    *line;
    int     n_cmd;
    int     n_pipes;
}   t_parse;

void     num_pipes(const char *line);
t_parse     *ps();
int     ms_isspaces(char c);
void    ps_error(char *msg);
void    pipe_ver_end(const char *line);
void    pipe_ver_start(const char *line);
void    pipe_ver_mid(const char *line);
int    pipe_ver_mid_help(const char *line, int i, int y);

# endif