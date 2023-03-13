/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:51:17 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/13 13:30:24 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exec(t_minishell *shell)
{
	int	tmp;

	tmp = 0;
	if (ft_lstsize(shell->list_cmd) == 1)
		exec_is_builtins(shell,((t_cmd *)shell->list_cmd->content)->cmd, shell->env);
	else
		ft_pipe(shell);
}

int main(int ac, char **av, char **env)
{	
	t_minishell *shell;
	t_cmd	*cmd;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	char *ar[] = {"ls", NULL};

	shell->list_cmd = NULL;
	shell->env = build_env_list(env);


	cmd = (t_cmd *)malloc(sizeof(cmd));
	cmd->cmd = ar;
	cmd->fd_in = 0;
	cmd->fd_out = 1;

	ft_lstadd_back(&shell->list_cmd, ft_lstnew(cmd));

	char *arv[] = {"ls",NULL};

	//shell->list_cmd = NULL;
	 cmd = (t_cmd *)malloc(sizeof(cmd));
	 cmd->cmd = arv;
	 cmd->fd_in = 0;
	 cmd->fd_out = 1;

	ft_lstadd_back(&shell->list_cmd, ft_lstnew(cmd));

	char *arv2[] = {"echo", " hamza" ,NULL};

	//shell->list_cmd = NULL;
	 cmd = (t_cmd *)malloc(sizeof(cmd));
	 cmd->cmd = arv2;
	 cmd->fd_in = 0;
	 cmd->fd_out = 1;

	ft_lstadd_back(&shell->list_cmd, ft_lstnew(cmd));

	// for (size_t i = 0; shell->list_cmd; i++)
	// {
	// 	printf("%s\n", *((t_cmd *)shell->list_cmd->content)->cmd);
	// 	shell->list_cmd = shell->list_cmd->next;
	// }
	// exit(0);

	ft_exec(shell);
}
