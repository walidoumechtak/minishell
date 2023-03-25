#include "minishell.h"

/*
*   Error infile -> 7
*   Error outfile and append -> 8
*   Error heredoc -> 9
*/
int	check_slach_symbole(t_minishell *ptr)
{
	t_list	*temp;
	DIR		*dir;

	temp = ptr->list_cmd;
	while (temp != NULL)
	{
		dir = opendir(((t_cmd *)temp->content)->cmd[0]);
		if (dir != NULL)
		{
			open_error(ptr, ((t_cmd *)temp->content)->cmd[0],
					": is a directory\n", 126);
			return (126);
		}
		temp = temp->next;
	}
	return (0);
}

int	mode1(t_minishell *ptr, t_cmd *link1, t_open_file *link2)
{
	if (link2->fd == -1)
	{
		link1->fd_in = -1;
		open_error(ptr, link2->file, ": No such file or directory\n", 1);
		ptr->exit_state = 1;
		return (7);
	}
	else
	{
		if (link1->fd_in > 2)
			close(link1->fd_in);
		link1->fd_in = link2->fd;
	}
	return (0);
}

int	other_mode(t_minishell *ptr, t_cmd *link1, t_open_file *link2)
{
	int	fd_out;

	if (link2->mode == 4)
	{
		if (link1->fd_in > 2)
			close(link1->fd_in);
		link1->fd_in = link2->fd;
	}
	else if ((link2->mode == 2 || link2->mode == 3))
	{
		fd_out = open_out_file(link2);
		if (fd_out < 0)
		{
			link1->fd_out = -1;
			open_error(ptr, link2->file, ": Permission denied\n", 1);
			return (8);
		}
		else
		{
			if (link1->fd_out > 2)
				close(link1->fd_out);
			link1->fd_out = fd_out;
		}
	}
	return (0);
}

int	complete_files(t_minishell *ptr)
{
	t_list		*temp;
	t_list		*temp2;
	t_cmd		*link1;
	t_open_file	*link2;
	int			state;

	temp = ptr->list_cmd;
	while (temp)
	{
		state = 0;
		link1 = ((t_cmd *)temp->content);
		temp2 = ((t_cmd *)temp->content)->opened_files;
		while (temp2 && state != 7)
		{
			link2 = ((t_open_file *)temp2->content);
			if (link2->mode == 1 && mode1(ptr, link1, link2) == 7)
				state = 7;
			else if (other_mode(ptr, link1, link2) == 8)
				return (8);
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	return (state);
}

int	build_linked_list(t_minishell *ptr)
{
	int		state;
	t_list	*temp;
	t_list	*temp2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	state = handle_quotes(ptr);
	if (state != 0)
		return (state);
	state = build_list_1(ptr);
	if (state != 0)
		return (state);
	state = build_list_2(ptr);
	if (state != 0)
		return (state);
	state = complete_files(ptr);
	if (state != 0)
		return (state);
	state = check_slach_symbole(ptr);
	if (state != 0)
		return (state);
	temp = ptr->list_cmd;
	while (temp)
	{
		i = 0;
		j = 0;
		while (((t_cmd *)temp->content)->cmd[i])
			printf("cmd[] : %s\n", ((t_cmd *)temp->content)->cmd[i++]);
		printf("in : %d\n", ((t_cmd *)temp->content)->fd_in);
		printf("out : %d\n", ((t_cmd *)temp->content)->fd_out);
		printf("---------------- end of pipe ------------------\n\n");
		printf("---------  the new list of files opened -----------\n");
		temp2 = ((t_cmd *)temp->content)->opened_files;
		while (temp2)
		{
			printf("file : %s\n", ((t_open_file *)temp2->content)->file);
			printf("fd : %d\n", ((t_open_file *)temp2->content)->fd);
			printf("mode : %d\n", ((t_open_file *)temp2->content)->mode);
			temp2 = temp2->next;
		}
		printf("-------- the end of new list ---------- \n\n");
		temp = temp->next;
	}
	return (0);
}
