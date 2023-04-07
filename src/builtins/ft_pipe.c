/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:30:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/07 11:26:55 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	dup_int_get_pid(int *fd, t_list *next, int pid)
{
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

static pid_t	exec_cmd(t_minishell *shell, t_cmd	*s_cmd, t_list *next)
{
	int		fd[2];
	int		s;
	char	*cmd;
	int		pid;

	pid = (pipe(fd), fork());
	if (!pid)
	{
		if (!s_cmd->cmd)
			(close(0), exit(0));
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (s_cmd->fd_in == -1 || s_cmd->fd_out == -1)
			exit(1);
		if (next != NULL && s_cmd->fd_out == STDOUT_FILENO)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(s_cmd->fd_out, STDOUT_FILENO);
		s = (close(fd[1]), exec_is_builtins(shell, s_cmd->cmd, shell->env));
		if (s != -1)
			exit(s);
		cmd = get_cmd_by_checkit_withpath(*s_cmd->cmd, shell->env);
		execve(cmd, s_cmd->cmd, convert_list_env(shell->env));
	}
	return (dup_int_get_pid(fd, next, pid));
}

static void	return_status(t_minishell *shell, int pid, int stdin)
{
	if (pid)
	{
		waitpid(pid, &shell->exit_state, 0);
		if (shell->exit_state == 2)
			shell->exit_state = 130;
		else if (shell->exit_state == 3)
			shell->exit_state = 131;
		else
			shell->exit_state = WEXITSTATUS(shell->exit_state);
	}
	else if (!pid)
		shell->exit_state = 0;
	while (wait(NULL) > 0)
		;
	close(0);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
}

void	ft_pipe(t_minishell *shell, t_list *cmd)
{
	int		stdin;
	pid_t	pid;

	pid = 0;
	stdin = dup(STDIN_FILENO);
	signal(SIGINT, SIG_IGN);
	if (((t_cmd *)(cmd->content))->fd_in)
		dup2(((t_cmd *)(cmd->content))->fd_in, STDIN_FILENO);
	while (cmd)
	{
		if (((t_cmd *)cmd->content)->fd_in == 1)
			dup2(stdin, STDIN_FILENO);
		else if (((t_cmd *)cmd->content)->fd_in > 1)
			dup2(((t_cmd *)cmd->content)->fd_in, STDIN_FILENO);
		pid = exec_cmd(shell, cmd->content, cmd->next);
		cmd = cmd->next;
	}
	return_status(shell, pid, stdin);
}
