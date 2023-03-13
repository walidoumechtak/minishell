/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:30:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/11 11:55:57 by hbenfadd         ###   ########.fr       */
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
	return (free_2d(tmp), ft_putstr_fd("command not found", 2), NULL);
}

static void exec_cmd(t_minishell *shell, t_list	*cmd, char *tmp)
{
	int	fd[2];
	int	r;

	r = 0;
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
		if ((r = exec_is_builtins(shell, shell->env) != -1))
			exit(r);
		else
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
					exec_cmd(shell, cmd, *args);
				else
					return (ft_putstr_fd("permission denied", 2), 1);
			}
			else
				return (ft_putstr_fd("command not found", 2), 1);
		}
		else
			exec_cmd(shell, cmd, check_cmd(ft_strjoin("/", *args), shell->env));
		cmd = cmd->next;
	}
	int a;
	wait(&a);
	printf("------%d\n", a);
	return (0);
}
 