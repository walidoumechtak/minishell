#include "minishell.h"



void	open_file(t_minishell *ptr, char **arr, int mode, int i)
{
	if (mode == 1)
	{
		if (ft_strncmp(arr[i + 1], "/dev/stdin", ft_strlen(arr[i + 1])) == 0)
			ptr->o_file->fd = 0;
		else if (ft_strncmp(arr[i + 1], "/dev/stdout", ft_strlen(arr[i
						+ 1])) == 0)
			ptr->o_file->fd = 1;
		else if (ft_strncmp(arr[i + 1], "/dev/stderr", ft_strlen(arr[i
						+ 1])) == 0)
			ptr->o_file->fd = 2;
		else
			ptr->o_file->fd = open(arr[i + 1], O_RDONLY);
		ptr->o_file->file = ft_strdup(arr[i + 1]);
		ptr->o_file->mode = 1;
		free_and_shift(arr, i);
	}
	else if (mode == 2)
	{
		ptr->o_file->file = ft_strdup(arr[i + 1]);
		ptr->o_file->mode = 2;
		free_and_shift(arr, i);
	}
	else if (mode == 3)
	{
		ptr->o_file->file = ft_strdup(arr[i + 1]);
		ptr->o_file->mode = 3;
		free_and_shift(arr, i);
	}
}

/*=====================================================================================================================*/
int	open_rederiction(t_minishell *ptr, t_list **old_node, t_cmd **new_cmd)
{
	t_list		*old;
	t_list		*new;
	t_cmd		*new_c;
	t_cmd_v1	*skin;
	int			i;
	int			k;
	int			l;

	//int j;
	i = 0;
	new_c = *new_cmd;
	old = *old_node;
	skin = (t_cmd_v1 *)old->content;
	new_c->opened_files = NULL;
	k = 0;
	l = 0;
	while (((t_cmd_v1 *)old->content)->cmd[i] && skin->cmd[i][0] != '\0')
	{
		if (ft_strncmp(skin->cmd[i], ">", ft_strlen(skin->cmd[i])) == 0
			&& skin->flags_red[k++] == 1)
		{
			ptr->o_file = malloc(sizeof(t_open_file));
			open_file(ptr, skin->cmd, 2, i);
		}
		else if (ft_strncmp(skin->cmd[i], "<", ft_strlen(skin->cmd[i])) == 0
				&& skin->flags_red[k++] == 1)
		{
			ptr->o_file = malloc(sizeof(t_open_file));
			open_file(ptr, skin->cmd, 1, i);
		}
		else if (ft_strncmp(skin->cmd[i], "<<", ft_strlen(skin->cmd[i])) == 0
				&& skin->flags_red[k++] == 1)
		{
			ptr->o_file = malloc(sizeof(t_open_file));
			if (skin->expaind_here[l] == 1)
			{
				ptr->o_file->fd = 0;
				if (open_heredoc(ptr, skin->cmd, i, 0) == 9)
					return (9);
				l++;
			}
			else
			{
				ptr->o_file->fd = 0;
				if (open_heredoc(ptr, skin->cmd, i, 404) == 9)
					return (9);
				l++;
			}
		}
		else if (ft_strncmp(skin->cmd[i], ">>", ft_strlen(skin->cmd[i])) == 0
				&& skin->flags_red[k++] == 1)
		{
			ptr->o_file = malloc(sizeof(t_open_file));
			open_file(ptr, skin->cmd, 3, i);
		}
		else if (skin->cmd == NULL)
			break ;
		else
		{
			i++;
			ptr->o_file = NULL;
		}
		if (ptr->o_file != NULL && skin->cmd != NULL)
		// create linked list of redrections < > << >>
		{
			new = ft_lstnew(ptr->o_file);
			if (!new)
				return (-1);
			ft_lstadd_back(&new_c->opened_files, new);
		}
	}
	return (0);
}

/*
	modes :
	1 --> infile
	2 --> outfile
	3 --> append
	4 --> heredoc
*/

/*=====================================================================================================================*/

/**
* build_list_2
	- building the final linked list that should be sned to execute part 
* we loop throw a linked list of file and their file descriptor and assigne to each node 
* hes **cmd and in_fd and out_fd
*/

int	build_list_2(t_minishell *ptr)
{
	t_list	*temp;
	t_list	*new;
	int		state;
	int		i;

	i = 0;
	ptr->signal_stop = 0;
	temp = ptr->list_v1;
	ptr->list_cmd = NULL;
	while (temp)
	{
		ptr->cmd = malloc(sizeof(t_cmd));
		ptr->cmd->fd_in = 0;
		ptr->cmd->fd_out = 1;
		state = open_rederiction(ptr, &temp, &ptr->cmd);
		if (state != 0)
			return (state);
		if (ptr->signal_stop == -9)
			return (-9);
		if (state != 0)
			return (state);
		ptr->cmd->cmd = ((t_cmd_v1 *)temp->content)->cmd;
		new = ft_lstnew(ptr->cmd);
		if (!new)
			return (-1);
		ft_lstadd_back(&ptr->list_cmd, new);
		temp = temp->next;
	}
	return (0);
}
