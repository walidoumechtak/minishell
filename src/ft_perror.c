#include "minishell.h"

int	ft_perror(t_minishell *ptr, char *str, int status)
{
	ft_putstr_fd(str, 2);
	ptr->exit_state = status;
	return (status);
}
