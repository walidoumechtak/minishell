/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:30:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/09 18:36:54by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stack_t char *
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

static char	*check_cmd(char *cmd, t_list *env)
{
	char	**tmp;
	char 	*tmp2;
	int		i;
	
	i = 0;
	tmp2 = NULL;
	tmp = NULL;
	cmd = ft_strjoin("/", cmd);
	while (env)
	{
		if (ft_strnstr(((t_env *)env->content)->env_var, "PATH", 4))
		{
			tmp = ft_split(((t_env *)env->content)->env_value, ':');
			break;
		}
		env = env->next;
	}
	while (tmp[i])
	{
		tmp2 = ft_strjoin(tmp[i], cmd);
		if(!access(tmp2, F_OK))
		{
			if (!access(tmp2, X_OK))
				return(free_2d(tmp), tmp2);
			else
				return(free_2d(tmp), perror("permission denied"), NULL);
		}
		free(tmp2);
		i++;
	}
	return (free_2d(tmp), perror("command not found"), NULL);
}

static void exec_cmd(t_list	*cmd, char *tmp)
{
	int	fd[2];

	if (!tmp)
		exit(0);
	pipe(fd);
	int pid1 = fork();
	if (pid1 == 0)
	{
		if (cmd->next != NULL && ((t_cmd *)(cmd->content))->fd_out == 1)
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(((t_cmd *)(cmd->content))->fd_out, 1);
		close(fd[1]);
		close(fd[0]);
		execve(tmp, ((t_cmd *)(cmd->content))->cmd, NULL);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

int	ft_pipe(t_minishell *shell)
{
	char **args;
	t_list *cmd;

	cmd = shell->list_cmd;
	args = NULL;
	if (!((t_cmd *)(shell->list_cmd->content))->fd_in)
		dup2(((t_cmd *)(shell->list_cmd->content))->fd_in, STDIN_FILENO);
	while (cmd)
	{
		args = (((t_cmd *)cmd->content)->cmd);
		if (!ft_isalnum(**args))
		{
			if (!access(*args, F_OK))
			{
				if (!access(*args, X_OK))
					exec_cmd(cmd, *args);
				else
					return (perror("permission denied"), 1);
			}
			else
				return (perror("command not found"), 1);
		}
		else
			exec_cmd(cmd, check_cmd(*args, shell->env));
		cmd = cmd->next;
	}
	wait(NULL);
	return (0);
}
 