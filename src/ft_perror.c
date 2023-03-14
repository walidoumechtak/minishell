#include "minishell.h"

void    ft_putchar_error(char c)
{
    write(2, &c, 1);
}

int    ft_perror(t_minishell *ptr, char *str, int status)
{
    int i;

    i = 0;
    while (str[i])
    {
        ft_putchar_error(str[i]);
        i++;
    }
    ptr->exit_state = status;
    return(status);
}