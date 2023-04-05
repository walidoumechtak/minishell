/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:51:17 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/05 10:59:25 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_null_cmd(t_minishell *shell)
{
	t_list	*cmd_list;
	int		i;
	char	**args;

	cmd_list = shell->list_cmd;
	while (cmd_list)
	{
		i = 0;
		while (((t_cmd *)cmd_list->content)->cmd[i])
		{
			printf("args[%d] = --%s--\n",i ,((t_cmd *)cmd_list->content)->cmd[i]);
			i++;
		}
		i = 0;
		args = ((t_cmd *)cmd_list->content)->cmd;
		while (args[i][0] == '\0')
		{
			printf("dax num %d\n", i);
			*((t_cmd *)cmd_list->content)->cmd = args[i + 1];
			free(args[i]);
		}
		i = 0;
		printf("------------\n");
		while (((t_cmd *)cmd_list->content)->cmd[i])
		{
			printf("args[%d] = --%s--\n",i ,((t_cmd *)cmd_list->content)->cmd[i]);
			i++;
		}
		
		cmd_list = cmd_list->next;
	}
}

void	ft_exec(t_minishell *shell)
{
	int	std[2];

	check_null_cmd(shell);
	if (ft_lstsize(shell->list_cmd) == 1)
	{
		if (((t_cmd *)shell->list_cmd->content)->fd_in == -1
			|| ((t_cmd *)shell->list_cmd->content)->fd_out == -1)
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
