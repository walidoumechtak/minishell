#include "minishell.h"

int	exec_is_builtins(t_minishell *shell, t_list *env)
{
	size_t	len;
	char	*cmd;
	char	**args;

	cmd = *((t_cmd *)shell->list_cmd->content)->cmd;
	args = ++((t_cmd *)shell->list_cmd->content)->cmd;
	len = ft_strlen(cmd);
	if (len == 4 && ft_strnstr(cmd, "echo", len))
		return (ft_echo(args));
	else if (len == 5 && ft_strnstr(cmd, "unset", len))
		return (ft_unset(shell, args));
		else if (len == 2 && ft_strnstr(cmd, "cd", len))
		return (ft_cd(args));
	else if (len == 3 && ft_strnstr(cmd, "env", len))
		return (ft_env(env));
	else if (len == 4 && ft_strnstr(cmd, "exit", len))
		return (ft_exit(args));
	// else if (len == 6 && ft_strnstr(cmd, "export", len))
	// 	return (ft_export(args));
	return (-1);
}