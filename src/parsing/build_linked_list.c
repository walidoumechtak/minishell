#include "minishell.h"

int    build_linked_list(t_minishell   *ptr)
{
    // t_list *temp;
    int state;
    // int i = 0;
    // int j = 0;

    state = handle_quotes(ptr);
    if (state != 0)
        return (state);
    state = build_list_1(ptr);
    if (state != 0)
        return (state);
    state = build_list_2(ptr);
    if (state != 0)
        return (state);
    // while (ptr->list_v1)
    // {
    //     i = 0;
    //     j = 0;
    //     while (((t_cmd_v1*)ptr->list_v1->content)->cmd[i])
    //         printf("%s\n", ((t_cmd_v1*)ptr->list_v1->content)->cmd[i++]);
    //     while (j < ((t_cmd_v1*)ptr->list_v1->content)->cpt_flags)
    //     {
    //         printf(" %d ", ((t_cmd_v1*)ptr->list_v1->content)->flags_red[j++]);
    //     }
    //     printf("-------\n");
    //     ptr->list_v1 = ptr->list_v1->next;
    // }
    // temp = ptr->list_cmd;
    // while (temp)
    // {
    //     i = 0;
    //     j = 0;
    //     while (((t_cmd*)temp->content)->cmd[i])
    //         printf("%s\n", ((t_cmd*)temp->content)->cmd[i++]);
    //     printf("in : %d\n", ((t_cmd*)temp->content)->fd_in);
    //     printf("out : %d\n", ((t_cmd*)temp->content)->fd_out);
    //     printf("---------------- end of pipe ------------------\n");
    //     temp = temp->next;
    // }
    return (0);
}