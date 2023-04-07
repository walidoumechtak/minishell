/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:31:53 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/07 10:25:14 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_is_builtins(t_minishell *shell, char **args, t_list *env)
{
	size_t	len;
	char	*cmd;

	cmd = *args;
	++args;
	len = ft_strlen(cmd);
	if (len == 4 && ft_strnstr(cmd, "echo", len))
		return (ft_echo(args));
	else if (len == 5 && ft_strnstr(cmd, "unset", len))
		return (ft_unset(shell, args));
	else if (len == 2 && ft_strnstr(cmd, "cd", len))
		return (ft_cd(shell, --args));
	else if (len == 3 && ft_strnstr(cmd, "env", len))
		return (ft_env(env));
	else if (len == 4 && ft_strnstr(cmd, "exit", len))
		return (ft_exit(shell, args));
	else if (len == 6 && ft_strnstr(cmd, "export", len))
		return (ft_export(shell, args));
	return (-1);
}
