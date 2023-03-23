/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:30:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/18 10:26:41hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_minishell *shell, t_cmd	*s_cmd, t_list *next)
{
	int		fd[2];
	int		s;
	char	*cmd;

	pipe(fd);
	if (fork() == 0)
	{
		if (s_cmd->fd_in == -1 || s_cmd->fd_in == -1)
			exit(1);
		if (next != NULL && s_cmd->fd_out == STDOUT_FILENO)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(s_cmd->fd_out, STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		s = exec_is_builtins(shell, s_cmd->cmd, shell->env);
		if (s != -1)
			exit(s);
		cmd = check_cmd(*s_cmd->cmd, shell->env);
		execve(cmd, s_cmd->cmd, convert_list_env(shell->env));
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

void	ft_pipe(t_minishell *shell, t_list *cmd)
{
	int	stdin;

	stdin = dup(STDIN_FILENO);
	if (((t_cmd *)(cmd->content))->fd_in)
		dup2(((t_cmd *)(cmd->content))->fd_in, STDIN_FILENO);
	while (cmd)
	{
		exec_cmd(shell, cmd->content, cmd->next);
		cmd = cmd->next;
	}
	while (wait(&shell->exit_state) > 0);
	shell->exit_state = WEXITSTATUS(shell->exit_state);
	dup2(stdin, STDIN_FILENO);
}