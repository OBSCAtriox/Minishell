#include "../../../includes/minishell.h"

void setup_prompt_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_prompt;     // define a função que trata SIGINT
    sigemptyset(&sa.sa_mask);        // não bloqueia sinais adicionais
    sa.sa_flags = 0;                 // comportamento padrão
    sigaction(SIGINT, &sa, NULL);    // aplica o handler
    signal(SIGQUIT, SIG_IGN);   
}

void sigint_prompt(int sig)
{
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    te()->exit_code = 130;
    tc()->g_sig = sig;
}

void    setup_exec_parent_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void    setup_exec_child_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}
