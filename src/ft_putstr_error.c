#include "minishell.h"

void    ft_putstr_error(char *str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while (str[i])
        ft_putchar_error(str[i++]);
}