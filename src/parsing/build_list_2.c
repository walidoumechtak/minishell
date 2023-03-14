#include "minishell.h"

int open_files(t_list **old_node, t_cmd **new_cmd)
{
    t_list  *old;
    t_cmd *data;

    data = *new_cmd;
    old = *old_node;
}

int build_list_2(t_minishell *ptr)
{
    t_list *temp;
    t_list *new;
    t_cmd   *cmd;
    int state;
    int i;
    int j;

    i = 0;
    temp = ptr->list_v1;
    ptr->list_cmd = NULL;
    while (temp)
    {
        cmd = malloc(sizeof(t_cmd));
        cmd->fd_in = 0;
        cmd->fd_out = 1;
        state = open_files(&temp, &cmd);
        if (state != 0) 
            return (state);

        new = ft_lstnew(cmd);
    }
}