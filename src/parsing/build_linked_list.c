#include "minishell.h"

int    build_linked_list(t_minishell   *ptr)
{
    int state;

    state = handle_quotes(ptr);
    if (state != 0)
        return (state);
    state = build_list_1(ptr);
    if (state != 0)
        return (state);
    state = build_list_2(ptr);
    if (state != 0)
        return (state);
    return (0);
}