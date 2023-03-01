#include "minishell.h"

int count_double_quotes(char *str)
{
    int i;
    int cpt;
    int cpt_inside_single_q;

    cpt = 0;
    cpt_inside_single_q = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            cpt++;
        i++;
    }
    return (cpt);
}

int count_singl_quotes(char *str)
{
    int i;
    int cpt;

    cpt = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            cpt++;
        i++;
    }
    return (cpt);
}

int check_is_quotes_close(t_minishell *ptr)
{
    int i;
    int j;

    i = 0;
    while (ptr->splited_pipe[i])
    {
        j = 0;
        while (ptr->splited_pipe[i][j])
        {
            // ================================
            if (ptr->splited_pipe[i][j] == '\"')
            {
                j++;
                while (ptr->splited_pipe[i][j] != '\"')
                {
                    j++;
                    if (ptr->splited_pipe[i][j] == '\0')
                        return (1);
                }
                j++;
                continue ;
            }
            // ================================
            else if (ptr->splited_pipe[i][j] == '\'')
            {
                j++;
                while (ptr->splited_pipe[i][j] != '\'')
                {
                    j++;
                    if (ptr->splited_pipe[i][j] == '\0')
                        return (1);
                }
                j++;
                continue ;
            }
            j++;
        }
        i++;
    }
    return (0);
}

void    remove_quotes(char *str)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {

    }
}

void    handle_quotes(t_minishell *ptr)
{
    int count_double_q;
    int count_singl_q;
    int i;
    int j;

    i = 0;
    if(check_is_quotes_close(ptr) == 1)
        ft_perror("Error : Sysntax Error\n", 1);
    while (ptr->splited_pipe[i])
    {
        j = 0;
        count_double_q = count_double_quotes(ptr->splited_pipe[i]); // remove double quotes
        count_singl_q = count_singl_quotes(ptr->splited_pipe[i]);
        remove_quotes(ptr->splited_pipe[i]);
        //ptr->splited_space = ft_split(ptr->splited_pipe[i], ' ');
        
        i++;
    }
}