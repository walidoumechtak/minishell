#include "minishell.h"

void open_error(t_minishell *ptr,char *file, char *str, int status)
{
    int i;

    i = 0;
    ft_putstr_fd(file, 2);
    ft_putstr_fd(str, 2);
    ptr->exit_state = status;
}