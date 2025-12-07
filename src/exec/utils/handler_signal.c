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
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    te()->exit_code = 130;
}