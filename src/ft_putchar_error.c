#include "minishell.h"

void    ft_putchar_error(char c)
{
    write(2, &c, 1);
}