/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:51:17 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/02 10:55:00 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_minishell *shell)
{
	int	std[2];

	if (ft_lstsize(shell->list_cmd) == 1)
	{
		if (((t_cmd *)shell->list_cmd->content)->fd_in == -1
			|| ((t_cmd *)shell->list_cmd->content)->fd_in == -1)
			return ;
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		if (((t_cmd *)shell->list_cmd->content)->fd_in)
			dup2(((t_cmd *)shell->list_cmd->content)->fd_in, STDIN_FILENO);
		if (((t_cmd *)shell->list_cmd->content)->fd_out > 2)
			dup2(((t_cmd *)shell->list_cmd->content)->fd_out, STDOUT_FILENO);
		shell->exit_state = exec_is_builtins(shell,
				((t_cmd *)shell->list_cmd->content)->cmd, shell->env);
		if (((t_cmd *)shell->list_cmd->content)->fd_in)
			dup2(std[0], STDIN_FILENO);
		if (((t_cmd *)shell->list_cmd->content)->fd_out > 2)
			dup2(std[1], STDOUT_FILENO);
		close(std[0]);
		close(std[1]);
	}
	if (ft_lstsize(shell->list_cmd) > 1 || shell->exit_state == -1)
		ft_pipe(shell, shell->list_cmd);
}
