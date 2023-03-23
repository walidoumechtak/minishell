/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:51:17 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/23 07:32:39 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_minishell *shell)
{
	if (ft_lstsize(shell->list_cmd) == 1)
		shell->exit_state = exec_is_builtins(shell,
				((t_cmd *)shell->list_cmd->content)->cmd, shell->env);
	else
		ft_pipe(shell, shell->list_cmd);
	if (shell->exit_state == -1)
		ft_pipe(shell, shell->list_cmd);
}
