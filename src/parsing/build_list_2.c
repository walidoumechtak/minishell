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
		//printf("fd in : %d \n", ptr->cmd->fd_in);
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
