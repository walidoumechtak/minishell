#include "minishell.h"

int	exec_is_builtins(t_minishell *shell, char **args, t_list *env)
{
	size_t	len;
	char	*cmd;

	cmd = *args;
	len = ft_strlen(cmd);
	if (len == 4 && ft_strnstr(cmd, "echo", len))
		exit (ft_echo(args));
	else if (len == 5 && ft_strnstr(cmd, "unset", len))
		exit (ft_unset(shell, args));
	else if (len == 2 && ft_strnstr(cmd, "cd", len))
		exit (ft_cd(args));
	else if (len == 3 && ft_strnstr(cmd, "env", len))
		exit (ft_env(env));
	else if (len == 4 && ft_strnstr(cmd, "exit", len))
		exit (ft_exit(args));
	// else if (len == 6 && ft_strnstr(cmd, "export", len))
	// 	return (ft_export(args));
	return (1);
}
