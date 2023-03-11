#include "minishell.h"

// int check_syntax_error_red(t_minishell *ptr)
// {
//     t_list  *temp;
//     t_cmd_v1 *alias;
//     int i;
//     int k;

//     temp = ptr->list_v1;
//     alias = (t_cmd_v1 *)temp->content;
//     while (temp)
//     {
//         i = 0;
//         k = 0;
//         while ((alias)->cmd[i])
//         {
//             if (alias->)
//         }
//         temp = temp->next;
//     }
// }

int    build_linked_list(t_minishell   *ptr)
{
    int state;
    int i = 0;
    int j = 0;

    state = handle_quotes(ptr);
    if (state != 0)
        return (state);
    state = build_list_1(ptr);
    if (state != 0)
        return (state);
    // state = check_syntax_error_red(ptr);
    // if (state != 0)
    //     return (state);
    while (ptr->list_v1)
    {
        i = 0;
        while (((t_cmd_v1*)ptr->list_v1->content)->cmd[i])
            printf("%s\n", ((t_cmd_v1*)ptr->list_v1->content)->cmd[i++]);
        while (j < ((t_cmd_v1*)ptr->list_v1->content)->cpt_flags)
        {
            printf(" %d ", ((t_cmd_v1*)ptr->list_v1->content)->flags_red[j++]);
        }
        printf("\n");
        ptr->list_v1 = ptr->list_v1->next;
    }
    return (0);
}