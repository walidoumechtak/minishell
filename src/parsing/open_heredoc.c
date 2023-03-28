/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:14:24 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/28 11:36:26 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int sig)
{
	(void)sig;
	exit(9);
}

/**
 * file_heredoc - create the file that conting all the data comming from stdin ,
	also before create the file the function
 * check if the name of the file is already exit or not
*/

void	file_heredoc(int rand, char **file)
{
	char	*char_rand;

	char_rand = ft_itoa(rand);
	*file = ft_strjoin("here_file", char_rand);
	while (access(*file, F_OK) == 0)
	{
		free(*file);
		free(char_rand);
		char_rand = ft_itoa(rand++);
		*file = ft_strjoin("here_file", char_rand);
	}
	free(char_rand);
}

/**
 * child_heredoc- in this function i fill the file with data
 *  coming form stdin and put it the file with ft_putstr_fd();
 * also has a signal function that exit the child proccess
 * whereever recieved a SIGINT siganl
*/

void	child_heredoc(t_minishell *ptr, char **arr, char *file, int *data)
{
	int		fd_file;
	char	*str;

	signal(SIGINT, signal_heredoc);
	fd_file = open(file, O_RDWR | O_CREAT, 0777);
	str = get_next_line(0);
	while (str != NULL)
	{
		if (ft_strncmp(str, arr[data[0] + 1], ft_strlen(str) - 1) == 0
			&& ft_strlen(str) > 1)
			break ;
		if (data[1] == 0)
			expaind_heredoc(ptr, &str);
		ft_putstr_fd(str, fd_file);
		free(str);
		str = get_next_line(0);
	}
	exit(0);
}

int	wait_and_fill_fd(t_minishell *ptr, char *file)
{
	int	e_s;

	wait(&e_s);
	if (WEXITSTATUS(e_s) == 9)
	{
		ptr->signal_stop = -9;
		ptr->exit_state = 1;
		return (9);
	}
	ptr->o_file->file = file;
	ptr->o_file->fd = open(file, O_RDONLY, 0777);
	ptr->o_file->mode = 4;
	return (0);
}

/**
 * open_ex_heredoc - open heredoc and any $USER should be expainded
*/

int	open_heredoc(t_minishell *ptr, char **arr, int i, int is_exp)
{
	static int	rand;
	char		*file;
	pid_t		pid;
	int			data[2];

	rand = 0;
	data[0] = i;
	data[1] = is_exp;
	file = NULL;
	file_heredoc(rand, &file);
	pid = fork();
	if (pid < 0)
		return (-2);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		child_heredoc(ptr, arr, file, data);
	else
	{
		if (wait_and_fill_fd(ptr, file) == 9)
			return (unlink(file), free(file), 9);
		free_and_shift(arr, i);
		rand++;
	}
	return (0);
}
