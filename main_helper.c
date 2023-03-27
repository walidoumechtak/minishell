/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:34:01 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/27 09:34:55 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_heredoc_files(t_minishell *ptr)
{
	t_list	*temp1;
	t_list	*temp2;

	temp1 = ptr->list_cmd;
	if (!temp1)
		return ;
	while (temp1)
	{
		temp2 = ((t_cmd *)temp1->content)->opened_files;
		if (!temp2)
			return ;
		while (temp2)
		{
			if (((t_open_file *)temp2->content)->mode == 4)
			{
				//free(((t_open_file *)temp2->content)->file);
				unlink(((t_open_file *)temp2->content)->file);
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
}

void	all_errors_parsing(t_minishell *ptr, int state)
{
	if (state == 1)
	{
		ft_perror(ptr, "Error : sysntax Error\n", 258);
	}
	else if (state == 9)
	{
		printf("here signal\n");
		remove_heredoc_files(ptr);
		free_linked_lists(ptr, 1);
		ptr->exit_state = 1;
	}
	else if (state == 7 || state == 8 || state == 126)
	{
		free_linked_lists(ptr, 1);
	}
}

void	close_fd(t_minishell *ptr)
{
	t_list	*temp;

	temp = ptr->list_cmd;
	while (temp)
	{
		if (((t_cmd *)temp->content)->fd_in > 2)
			close(((t_cmd *)temp->content)->fd_in);
		if (((t_cmd *)temp->content)->fd_out > 2)
			close(((t_cmd *)temp->content)->fd_out);
		temp = temp->next;
	}
}

/**
 * signal_handler1 - function that handle the SIGINT signal in the main proccess
*/

void	signal_handler1(int sig)
{
	if (sig == SIGINT)
	{
		free_flag = 1;
		write(STDOUT_FILENO, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	end_of_program(t_minishell *ptr)
{
	close_fd(ptr);
	remove_heredoc_files(ptr);
	free(ptr->str);
	free_spilte(ptr->splited_pipe);
	free_linked_lists(ptr, 1);
}