#include "minishell.h"

void	free_list_v1(t_minishell *ptr, t_list *temp2)
{
	if (temp2 == NULL)
		return ;
	while (temp2)
	{
		free(((t_cmd_v1 *)temp2->content)->flags_red);
		free(((t_cmd_v1 *)temp2->content)->expaind_here);
		free_spilte(((t_cmd_v1 *)temp2->content)->cmd);
		temp2 = temp2->next;
	}
	ft_lstclear(&ptr->list_v1, del);
}

void	free_list_v2(t_minishell *ptr, t_list *temp1, t_list *temp4)
{
	t_cmd	*link_ofile;

	while (temp1)
	{
		//free_spilte(((t_cmd *)temp1->content)->cmd);
		link_ofile = ((t_cmd *)temp1->content);
		if (link_ofile->fd_in > 2)
			close(link_ofile->fd_in);
		if (link_ofile->fd_out > 2)
			close(link_ofile->fd_out);
		temp4 = link_ofile->opened_files;
		while (link_ofile->opened_files)
		{
			free(((t_open_file *)link_ofile->opened_files->content)->file);
			if (((t_open_file *)link_ofile->opened_files->content)->fd > 2)
				close(((t_open_file *)link_ofile->opened_files->content)->fd);
			link_ofile->opened_files = link_ofile->opened_files->next;
		}
		ft_lstclear(&temp4, del);
		//free_spilte(((t_cmd *)temp1->content)->cmd);
		temp1 = temp1->next;
	}
	ft_lstclear(&ptr->list_cmd, del);
}

void	free_linked_lists(t_minishell *ptr, int flag)
{
	t_list	*temp1;
	t_list	*temp3;
	t_list	*temp4;

	temp1 = ptr->list_cmd;
	temp3 = ptr->env;
	temp4 = NULL;
	free_list_v1(ptr, ptr->list_v1);
	if (flag == 1)
		free_list_v2(ptr, temp1, temp4);
}
