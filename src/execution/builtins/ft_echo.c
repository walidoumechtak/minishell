#include "minishell.h"

void	ft_echo(char *str, char flag)
{
	if (flag == 'n')
		printf("%s\n", str);
	else
		printf("%s", str);
}
