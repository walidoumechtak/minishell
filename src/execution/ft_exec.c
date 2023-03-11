/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:51:17 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/11 11:52:42 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtins(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (len == 4 && ft_strnstr(cmd, "echo", len))
		return (1);
	else if (len == 5 && ft_strnstr(cmd, "unset", len))
		return (2);
	else if (len == 6 && ft_strnstr(cmd, "export", len))
		return (3);
	else if (len == 2 && ft_strnstr(cmd, "cd", len))
		return (4);
	else if (len == 3 && ft_strnstr(cmd, "env", len))
		return (5);
	else if (len == 4 && ft_strnstr(cmd, "exit", len))
		return (6);
	return (0);
}

void	ft_exec(t_minishell *shell)
{
	int	tmp;

	tmp = 0;
	if (ft_lstsize(shell->list_cmd) == 1)
	{
		tmp = is_builtins(*((t_cmd *)(shell->list_cmd->content))->cmd);
		if (tmp != 0)
		{
			if (tmp == 1)
				ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
			else if (tmp == 5)
				ft_env(shell->env);
			else if (tmp == 4)
				ft_cd(++((t_cmd *)(shell->list_cmd->content))->cmd);
			else if (tmp == 2)
				ft_unset(shell, ++((t_cmd *)(shell->list_cmd->content))->cmd);
			// else if (tmp == 5)
			// 	ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
			// else if (tmp == 6)
			// 	ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
		}
	}
	else
		ft_pipe(shell);
}

int main(int ac, char **av, char **env)
{	
	t_minishell *shell;
	t_cmd	*cmd;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	char *ar[] = {"echo", "LANG", "COLORTERM", NULL};

	shell->list_cmd = NULL;
	shell->env = build_env_list(env);


	cmd = (t_cmd *)malloc(sizeof(cmd));
	cmd->cmd = ar;
	cmd->fd_in = 0;
	cmd->fd_out = 1;

	ft_lstadd_back(&shell->list_cmd, ft_lstnew(cmd));

	char *arv[] = {"env", "a", NULL};

	//shell->list_cmd = NULL;
	 cmd = (t_cmd *)malloc(sizeof(cmd));
	 cmd->cmd = arv;
	 cmd->fd_in = 0;
	 cmd->fd_out = 1;

	ft_lstadd_back(&shell->list_cmd, ft_lstnew(cmd));
	ft_exec(shell);
}
