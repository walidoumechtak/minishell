#include "minishell.h"

void    ft_putchar_error(char c)
{
    write(2, &c, 1);
}

int    ft_perror(char *str, int status)
{
    int i;

    i = 0;
    while (str[i])
    {
        ft_putchar_error(str[i]);
        i++;
    }
    STAT = status;
    return(status);
    //exit(status);
    // return (status);
}