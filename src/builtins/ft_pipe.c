/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:30:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/27 15:56:17by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_in_execcmd(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT)
		return ;
}

static pid_t	exec_cmd(t_minishell *shell, t_cmd	*s_cmd, t_list *next)
{
	int		fd[2];
	int		s;
	char	*cmd;
	int		pid;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		if (s_cmd->fd_in == -1 || s_cmd->fd_out == -1)
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
		cmd = get_cmd_by_checkit_withpath(*s_cmd->cmd, shell->env);
		execve(cmd, s_cmd->cmd, convert_list_env(shell->env));
	}
	if (next)
		dup2(fd[0], STDIN_FILENO);
	else
		close(0);
	close(fd[1]);
	close(fd[0]);
	if (!next)
		return (pid);
	return (0);
}

void	ft_pipe(t_minishell *shell, t_list *cmd)
{
	int		stdin;
	pid_t	pid;

	pid = 0;
	stdin = dup(STDIN_FILENO);
	signal(SIGINT, signal_handler_in_execcmd);
	if (((t_cmd *)(cmd->content))->fd_in)
		dup2(((t_cmd *)(cmd->content))->fd_in, STDIN_FILENO);
	while (cmd)
	{
		if (*((t_cmd *)cmd->content)->cmd)
		{
			if (((t_cmd *)cmd->content)->fd_in == 1)
				dup2(stdin, STDIN_FILENO);
			else if (((t_cmd *)cmd->content)->fd_in > 1)
				dup2(((t_cmd *)cmd->content)->fd_in, STDIN_FILENO);
			pid = exec_cmd(shell, cmd->content, cmd->next);
		}
		cmd = cmd->next;
	}
	if (pid)
	{
		waitpid(pid, &shell->exit_state, 0);
		shell->exit_state = WEXITSTATUS(shell->exit_state);
	}
	else if (!pid)
		shell->exit_state = 0;
	while (wait(NULL) > 0)
		;
	dup2(stdin, STDIN_FILENO);
	close(stdin);
}
