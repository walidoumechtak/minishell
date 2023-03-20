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

// int check_is_quotes_close(t_minishell *ptr)
// {
//     int i;
//     int j;

//     i = 0;
//     while (ptr->splited_pipe[i])
//     {
//         j = 0;
//         while (ptr->splited_pipe[i][j])
//         {
//             // ================================
//             if (ptr->splited_pipe[i][j] == '\"')
//             {
//                 j++;
//                 if (ptr->splited_pipe[i][j] == '\0')
//                     return (1);
//                 while (ptr->splited_pipe[i][j] != '\"')
//                 {
//                     j++;
//                     if (ptr->splited_pipe[i][j] == '\0')
//                         return (1);
//                 }
//                 j++;
//                 continue ;
//             }
//             // ================================
//             else if (ptr->splited_pipe[i][j] == '\'')
//             {
//                 j++;
//                 if (ptr->splited_pipe[i][j] == '\0')
//                     return (1);
//                 while (ptr->splited_pipe[i][j] != '\'')
//                 {
//                     j++;
//                     if (ptr->splited_pipe[i][j] == '\0')
//                         return (1);
//                 }
//                 j++;
//                 continue ;
//             }
//             j++;
//         }
//         i++;
//     }
//     return (0);
// }

void    add_space_redirection(char **str)
{
    char *temp;
    char *iter;
    int size;
    int i;
    int j;
    
    i = 0;
    j = -1;
    if (!str || !*str)
        return;
    size = (is_there_append(*str) + is_there_heredoc(*str) + is_there_in_redirection(*str) + is_there_out_redirection(*str)) * 2 + 2;
    //size = (is_there_append(*str) + is_there_heredoc(*str) + is_there_in_redirection(*str) + is_there_out_redirection(*str));
    //printf("size ---------------------------------------------------> : %d\n", size);
    temp = malloc((ft_strlen(*str) + size + 1) * sizeof(char));
    iter = *str;
    while (iter[i])
    {
        if (iter[i] == '\"')
        {
            temp[++j] = iter[i];
            i++;
            while (iter[i] && iter[i] != '\"')
                temp[++j] = iter[i++];
            temp[++j] = iter[i];
        }
        else if (iter[i] == '\'')
        {
            temp[++j] = iter[i];
            i++;
            while (iter[i] && iter[i] != '\'')
                temp[++j] = iter[i++];
            temp[++j] = iter[i];
        }
        else
        {
            if (iter[i] != '>' && iter[i] != '<')
                temp[++j] = iter[i];
            else
            {
                while (iter[i] == '>' || iter[i] == '<')
                {
                    if (iter[i] == '>')
                    {
                        temp[++j] = ' ';
                        while (iter[i] == '>')
                            temp[++j] = iter[i++];
                    }
                    if (iter[i] == '<')
                    {
                        temp[++j] = ' ';
                        while (iter[i] == '<')
                            temp[++j] = iter[i++];   
                    }
                }
                i--;
                temp[++j] = ' ';
            }
        }
        i++;
    }
    temp[++j] = '\0';
    //printf("j is : %d\n", j);
    //printf("the length is : %zu\n", ft_strlen(*str));
    free(*str);
    *str = temp;
}

void    add_space_one(char **str)
{
    char *temp = NULL;
    char *iter;
    int size;
    int i;
    int j;

    i = 0;
    j = -1;
    size = (is_there_in_redirection(*str) * 2) + (is_there_out_redirection(*str) * 2);
    temp = malloc((ft_strlen(*str) + size) * sizeof(char));
    iter = *str;
    while (iter[i])
    {
        if (iter[i] == '\"')
        {
            temp[++j] = iter[i];
            i++;
            while (iter[i] && iter[i] != '\"')
                temp[++j] = iter[i++];
            temp[++j] = iter[i];
        }
        else if (iter[i] == '\'')
        {
            temp[++j] = iter[i];
            i++;
            while (iter[i] && iter[i] != '\'')
                temp[++j] = iter[i++];
            temp[++j] = iter[i];
        }
        else
        {
            if (iter[i] != '>' && iter[i] != '<')
                temp[++j] = iter[i];
            else if (iter[i] == '>')
            {
                temp[++j] = ' ';
                temp[++j] = '>';
                temp[++j] = ' ';
            }
            else if (iter[i] == '<')
            {
                temp[++j] = ' ';
                temp[++j] = '<';
                temp[++j] = ' ';
            }
        }
        i++;
    }
    temp[++j] = '\0';
    free(*str);
    *str = temp;
}



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