#include "minishell.h"

void open_error(t_minishell *ptr,char *file, char *str, int status)
{
    int i;

    i = 0;
    ft_putstr_error(file);
    ft_putstr_error(str);
    ptr->exit_state = status;
}