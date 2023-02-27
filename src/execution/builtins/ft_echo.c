#include "minishell.h"

int	ft_echo(char **args, char *flag)
{
	while (args && *args)
	{
		printf("%s", *args);
		args++;
		if (args && *args)
			printf(" ");
	}
	if (!flag || !*flag || !ft_strncmp(flag, "-n", 2))
		printf("\n");
	return (0);
}
