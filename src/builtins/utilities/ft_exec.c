/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:51:17 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/25 15:20:07 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_minishell *shell)
{
	int	stdin;
	int	stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (ft_lstsize(shell->list_cmd) == 1)
	{
		if (((t_cmd *)shell->list_cmd->content)->fd_in)
			dup2(((t_cmd *)shell->list_cmd->content)->fd_in, STDIN_FILENO);
		if (((t_cmd *)shell->list_cmd->content)->fd_out > 2)
			dup2(((t_cmd *)shell->list_cmd->content)->fd_out, STDOUT_FILENO);
		shell->exit_state = exec_is_builtins(shell,
				((t_cmd *)shell->list_cmd->content)->cmd, shell->env);
		if (((t_cmd *)shell->list_cmd->content)->fd_in)
			dup2(stdin, STDIN_FILENO);
		if (((t_cmd *)shell->list_cmd->content)->fd_out > 2)
			dup2(stdout, STDOUT_FILENO);
		close(stdin);
		close(stdout);
	}
	else
		ft_pipe(shell, shell->list_cmd);
	if (shell->exit_state == -1)
		ft_pipe(shell, shell->list_cmd);
}
