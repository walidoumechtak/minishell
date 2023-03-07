/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:30:59 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/07 11:38:11 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_minishell *shell)
{
	int	fd[2];
	char **args;
	t_list *lst_tmp;

	lst_tmp = shell->list_cmd;
	args = NULL;
	int infile = ((t_cmd *)(shell->list_cmd->content))->fd_in;
	dup2(infile, STDIN_FILENO);
	while (lst_tmp != NULL)
	{
		pipe(fd);
		int pid1 = fork();
		if (pid1 == 0)
		{
			args = ((t_cmd *)(lst_tmp->content))->cmd;
			if (lst_tmp->next != NULL && ((t_cmd *)(lst_tmp->content))->fd_out == 1) 
				dup2(fd[1], STDOUT_FILENO);
			else 
				dup2(((t_cmd *)(lst_tmp->content))->fd_out, 1);
			close(fd[1]);
			close(fd[0]);
			execve(*args, args, NULL);
		}
		 
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			lst_tmp = lst_tmp->next;
	}
	wait(NULL);
	return (0);
}
