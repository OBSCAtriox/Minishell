#include "includes/minishell.h"

t_env	*te(void)
{
	static t_env	env;

	return (&env);
}

t_pipeline	*ms(void)
{
	static t_pipeline	ms;

	return (&ms);
}

/* static void	printf_list_tok(t_per_cmd_tok *tl)
{
	t_tokens	*tmp;

	while (tl)
	{
		printf("\n//////////////////////\n");
		tmp = tl->cmdt;
		while (tmp)
		{
			printf("list of tok list : --> %s\n", tmp->value);
			printf("\n------------------\n");
			tmp = tmp->next;
		}
		tl = tl->next;
	}
} */

int	main(int argc, char **argv, char **envp)
{
			//int count;
			//t_per_cmd_tok *tl;
	//t_tokens	*cur;
	//int			y;

	// int i;
	// i = 0;
	(void)argv;
	if (argc != 1)
		basic_error(ERR_ARG);
	mount_envp(envp);
	// printf("%s\n", expand_line("Ola $? $9 boas \"$1\""));
	while (1)
	{
		ps()->line = readline("T_Shell> ");
		add_history(ps()->line);
		if (verifications(ps()->line))
		{
			if (!ps()->tok)
				printf("list NULL\n");
			for (t_tokens *tmp = ps()->tok; tmp; tmp = tmp->next)
				printf("Value: %s, type: %d\n", tmp->value, tmp->type);
			/* while (te()->envp[i])
			{
				write(1, te()->envp[i], ft_strlen(te()->envp[i]));
				write(1, "\n", 1);
				i++;
			}
			printf("\n\n%s\n\n\n", ps()->line);
			printf("break 1\n");
			count = 0;
			printf("\n\n\n---------------------------\n\n");
			tl = ps()->tl;
			while (tl)
			{
				cur = tl->cmdt;
				while (cur)
				{
					printf("list of tok: --> %s\n", cur->value);
					cur = cur->next;
				}
				printf("\n-------------------------\n");
				tl = tl->next;
			}
			if (!ms()->cmdv)
				printf("no ms\n");
			while (ms()->cmdv[count])
			{
				y = 0;
				printf("break 2\n");
				printf("\n\n-----%d-----\n\n", count);
				while (ms()->cmdv[count]->argv[y])
				{
					printf("%d --> argv ", y);
					printf("%s\n", ms()->cmdv[count]->argv[y]);
					printf("------------------------\n");
					y++;
				}
				count++;
			}
			printf("\n\n\n--------|-------\n");
			printf_list_tok(ps()->tl);
			printf("\n\n\n----------------\n");
			count = 0;
			while (ms()->cmdv[count])
			{
				int i;
				i = 0;
				while (ms()->cmdv[count]->redir[i])
				{
					printf_redirs_info(ms()->cmdv[count]->redir[i], i);
					i++;
				}
				printf("#builtin?---> %d\n", ms()->cmdv[count]->is_builtin);
				count++;
			} */
		print_minishell_structs(1);
		free_all("Cleaning after command\n", 0);
		}
		ps()->line = NULL;
	}
}
