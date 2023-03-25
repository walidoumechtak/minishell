/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:14:24 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/25 15:14:29 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	signal_heredoc(int sig)
{
	(void)sig;
	free_flag = 1;
	exit(9);
}

/**
 * open_ex_heredoc - open heredoc and any $USER should be expainded
*/

int	open_heredoc(t_minishell *ptr, char **arr, int i, int is_exp)
{
	static int	rand;
	char		*char_rand;
	char		*file;
	char		*str;
	int			e_s;
	int			fd_file;
	pid_t		pid;

	// struct sigaction action;
	// action.sa_handler = signal_handler3;
	// sigemptyset(&action.sa_mask);
	// action.sa_flags = 0;
	// sigaction(SIGINT, &action, NULL);
	rand = 0;
	char_rand = ft_itoa(rand);
	file = ft_strjoin("/tmp/here_file", char_rand);
	while (access(file, F_OK) == 0)
	{
		free(file);
		free(char_rand);
		char_rand = ft_itoa(rand++);
		file = ft_strjoin("/tmp/here_file", char_rand);
	}
	free(char_rand);
	pid = fork();
	if (pid < 0)
		return (-2);
	if (pid == 0)
	{
		signal(SIGINT, signal_heredoc);
		fd_file = open(file, O_RDWR | O_CREAT, 0777);
		str = get_next_line(0);
		while (str != NULL)
		{
			if (ft_strncmp(str, arr[i + 1], ft_strlen(str) - 1) == 0
				&& ft_strlen(str) > 1)
				break ;
			if (is_exp == 0)
				expaind_heredoc(ptr, &str);
			ft_putstr_fd(str, fd_file);
			free(str);
			str = get_next_line(0);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &e_s, 0);
		if (WEXITSTATUS(e_s) == 9)
		{
			ptr->signal_stop = -9;
			ptr->exit_state = 1;
			return (9);
		}
		ptr->o_file->file = file;
		ptr->o_file->fd = open(file, O_RDONLY, 0777);
		ptr->o_file->mode = 4;
		free_and_shift(arr, i);
		rand++;
	}
	return (0);
}