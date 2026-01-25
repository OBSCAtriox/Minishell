/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:10:13 by thde-sou          #+#    #+#             */
/*   Updated: 2026/01/18 23:49:35 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc(void)
{
	t_data	dt;
	t_cmd	**cmdv;
	t_redir	**redir;

	dt.i = 0;
	cmdv = ms()->cmdv;
	tc()->signaled_heredoc = 0;
	while (cmdv[dt.i])
	{
		redir = cmdv[dt.i]->redir;
		dt.j = 0;
		while (redir && redir[dt.j])
		{
			if (redir[dt.j]->type == R_HDOC && !tc()->signaled_heredoc)
			{
				if (!mount_heredoc(dt.i, dt.j))
					return (FALSE);
			}
			dt.j++;
		}
		dt.i++;
	}
	return (TRUE);
}

int	mount_heredoc(int idx_cmd, int idx_rdir)
{
	int		fd[2];
	pid_t	pid;
	char	*delim;

	delim = ms()->cmdv[idx_cmd]->redir[idx_rdir]->path;
	if (pipe(fd) < 0)
		return (perror("pipe"), FALSE);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close_all(fd[0], fd[1], -1, -1), FALSE);
	signal(SIGINT, SIG_IGN);
	if (pid == 0 && !tc()->signaled_heredoc)
		read_heredoc(idx_cmd, idx_rdir, fd, delim);
	close(fd[1]);
	ms()->cmdv[idx_cmd]->redir[idx_rdir]->hdoc_fd = fd[0];
	wait_heredoc(pid, fd);
	setup_prompt_signal();
	if (te()->exit_code == 130)
		return (FALSE);
	return (TRUE);
}

void	read_heredoc(int idx_cmd, int idx_rdir, int *fd, char *delim)
{
	char	*line;
	int		quoted;

	close(fd[0]);
	close_fd_redir();
	setup_heredoc_signals(fd[1]);
	quoted = ms()->cmdv[idx_cmd]->redir[idx_rdir]->quoted;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error_hdoc(delim);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write_line(quoted, line, fd[1]);
		free(line);
	}
	exit_heredoc(fd[1]);
}

void	write_line(int quoted, char *line, int fd)
{
	char	*exp;

	exp = NULL;
	if (!quoted)
	{
		exp = expand_line(line);
		if (!exp)
		{
			free(line);
			exit(1);
		}
		ft_putendl_fd(exp, fd);
	}
	else
		ft_putendl_fd(line, fd);
	if (exp)
		free(exp);
}

void	setup_heredoc_signals(int fd)
{
	struct sigaction	sa;

	tc()->hdoc_wfd = fd;
	sa.sa_handler = sigint_hdoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
