#include "minishell.h"

void    build_linked_list_v1(t_minishell   *ptr)
{
    // t_cmd   *cmd;
    // int cpt_in_red;

    ptr->list_v1 = NULL;
    handle_quotes(ptr);
    // while (ptr->splited_pipe)
    // {
    //     cpt_in_red = is_there_in_redirection(ptr);
    //     cmd = malloc(sizeof(t_cmd));
    // }
}