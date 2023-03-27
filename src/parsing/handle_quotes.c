#include "minishell.h"




int    handle_quotes(t_minishell *ptr)
{
    int i;
    
    i = 0;
    while (ptr->splited_pipe[i])
    {
        fill_with(ptr->splited_pipe[i], '\t', '|');
        fill_with(ptr->splited_pipe[i], ' ', '\t');
        add_space_redirection(&ptr->splited_pipe[i]);
        if (rederction_syntax(ptr->splited_pipe[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}