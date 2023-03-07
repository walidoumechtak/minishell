#include "minishell.h"

int    build_linked_list(t_minishell   *ptr)
{
    int state;
    int i = 0;

    state = handle_quotes(ptr);
    if (state != 0)
        return (state);
    state = build_list_1(ptr);
    if (state)
        return (state);
    while (ptr->list_v1)
    {
        i = 0;
        while (((t_cmd_v1*)ptr->list_v1->content)->cmd[i])
            printf("%s\n", ((t_cmd_v1*)ptr->list_v1->content)->cmd[i++]);
        ptr->list_v1 = ptr->list_v1->next;
    }
    return (0);
}