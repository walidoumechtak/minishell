/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:30:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/18 11:20:43 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void free_2d(char **ptr)
{
	int i;

	i = 0;
	while(ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static	char **get_path(t_list *env)
{
	while (env)
	{
		if (ft_strnstr(((t_env *)env->content)->env_var, "PATH", 4))
			return (ft_split(((t_env *)env->content)->env_value, ':'));
		env = env->next;
	}
	return (NULL);
}

static char	*check_cmd(char *cmd, t_list *env)
{
	char	**tmp;
	char 	*tmp2;
	int		i;
	
	i = 0;
	tmp2 = NULL;
	tmp	= get_path(env);
	while (tmp[i])
	{
		tmp2 = ft_strjoin(tmp[i], cmd);
		if(!access(tmp2, F_OK))
		{
			if (!access(tmp2, X_OK))
				return(free_2d(tmp), tmp2);
			else
				return(free_2d(tmp), ft_putstr_fd("permission denied", 2), NULL);
		}
		free(tmp2);
		i++;
	}
	return (free_2d(tmp), ft_putstr_fd(&cmd[1], 2), ft_putstr_fd(": command not found\n", 2), NULL);
}

static void	exec_cmd(t_minishell *shell, t_list	*cmd)
{
	int		fd[2];
	int		a;
	char	*tmp;

	pipe(fd);
	if (fork() == 0)
	{
		if (((t_cmd *)(shell->list_cmd->content))->fd_in == -1 ||
			((t_cmd *)(shell->list_cmd->content))->fd_in == -1)
			exit(1);
		if (cmd->next != NULL && ((t_cmd *)(cmd->content))->fd_out == 1)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(((t_cmd *)(cmd->content))->fd_out, 1);
		close(fd[1]);
		close(fd[0]);
		a = exec_is_builtins(shell, ((t_cmd *)(cmd->content))->cmd, shell->env);
		if (a == -1)
		{
			tmp = check_cmd(ft_strjoin("/", *((t_cmd *)cmd->content)->cmd), shell->env);
			if (!tmp)
				exit(127);
			execve(tmp, ((t_cmd *)(cmd->content))->cmd, convert_list_env(shell->env));
		}
		exit(a);
	}
	if (cmd->next != NULL)
		dup2(fd[0], STDIN_FILENO);
	else
		dup2(0, STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

int	ft_pipe(t_minishell *shell)
{
	char	**args;
	t_list	*cmd;
	int		stdin;
	int		stdout;
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	cmd = shell->list_cmd;
	args = NULL;
	if (((t_cmd *)(shell->list_cmd->content))->fd_in)
		dup2(((t_cmd *)(shell->list_cmd->content))->fd_in, STDIN_FILENO);
	while (cmd)
	{
		args = (((t_cmd *)cmd->content)->cmd);
		if (!ft_isalnum(**args))
		{
			if (!access(*args, F_OK))
			{
				if (!access(*args, X_OK))
					execve(*args, args, NULL);
				else
					return (ft_putstr_fd(*args, 2), ft_putstr_fd(": permission denied\n", 2), 1);
			}
			else
				return (ft_putstr_fd(*args, 2), ft_putstr_fd(": command not found", 2), 127);
		}
		else
			exec_cmd(shell, cmd);
		cmd = cmd->next;
	}
	while (wait(&shell->exit_state) > 0);
	wait(&shell->exit_state);
	shell->exit_state = WEXITSTATUS(shell->exit_state);
	dup2(stdout, STDOUT_FILENO);
	dup2(stdin, STDIN_FILENO);
	return (0);
}
