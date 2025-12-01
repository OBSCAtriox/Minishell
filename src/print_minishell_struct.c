#include "../includes/minishell.h"

void	print_minishell_structs(int n)
{
	int	i;
	int	count;
	int	y;

	i = 0;
	count = 0;
	if (n == 1)
	{
		if(ms()->cmdv)
		{
			while (ms()->cmdv[count])
			{
				printf(BFGMAGEN BOLD"------------%d command------------\n", count + 1);
				printf("Command: %s\n", ms()->cmdv[count]->argv[0]);
				i = 0;
				if(ms()->cmdv[count]->redir)
				{
					while (ms()->cmdv[count]->redir[i])
					{
						printf("|   # Path: --> %s\n",
							ms()->cmdv[count]->redir[i]->path);
						printf("|   # Fd_target: --> %d\n",
							ms()->cmdv[count]->redir[i]->fd_target);
						printf("|   # Quoted: --> %d\n",
							ms()->cmdv[count]->redir[i]->quoted);
						printf("|   # Hdoc_fd: --> %d\n",
							ms()->cmdv[count]->redir[i]->hdoc_fd);
        	    	    i++;
					}
				}
				printf("|\n|   # Is_builtin: --> %d\n",
					ms()->cmdv[count]->is_builtin);
				printf("|   # Argv: --> ");
        	    y = 0;
				while (ms()->cmdv[count]->argv[y])
					printf("%s   /|\\   ", ms()->cmdv[count]->argv[y++]);
				printf(RESET"\n\n\n");
        	    count++;
			}
		}
		
	}
}
