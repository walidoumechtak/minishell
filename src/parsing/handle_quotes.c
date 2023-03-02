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

void    fill_sapce_with(char *str, char c)
{
    int i;

    if (!str)
        return ;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
            {
                if (str[i] == ' ')
                    str[i] = c;
                i++;
            }
            // i++;
        }
        else if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
            {
                if (str[i] == ' ')
                    str[i] = c;
                i++;
            }
            // i++;
        }
        i++;
    }

}

void    add_space_double(char **str)
{
    char *temp;
    char *iter;
    int size;
    int i;
    int j;
    
    i = 0;
    j = -1;
    size = is_there_append(*str) * 2 + is_there_heredoc(*str) * 2;
    temp = malloc((ft_strlen(*str) + size) * sizeof(char));
    iter = *str;
    while (iter[i])
    {
        if (iter[i] == '\"' || iter[i] == '\'')
        {
            i++;
            while (iter[i] && (iter[i] != '\"' || iter[i] != '\''))
                temp[++j] = iter[i++];
        }
        else
        {
            if (iter[i] != '>' && iter[i] != '<')
                temp[++j] = iter[i];
            else if (iter[i] == '>' && iter[i] && iter[i + 1] == '>')
            {
                temp[++j] = ' ';
                temp[++j] = '>';
                temp[++j] = '>';
                temp[++j] = ' ';
                i += 2;
                continue ;
            }
            else if (iter[i] == '<' && iter[i] && iter[i + 1] == '<')
            {
                temp[++j] = ' ';
                temp[++j] = '<';
                temp[++j] = '<';
                temp[++j] = ' ';
                i += 2;
                continue ;
            }
        }
        i++;
    }
}

// void    add_space_double(char **str)
// {
//     char *temp;
//     char *iter;
//     int size;
//     int i;
//     int j;
    
//     i = 0;
//     j = -1;
//     size = is_there_append(*str) * 2 + is_there_heredoc(*str) * 2;
//     temp = malloc((ft_strlen(*str) + size) * sizeof(char));
//     iter = *str;
//     while (iter[i])
//     {
//         if (iter[i] != '>' && iter[i] != '<')
//             temp[++j] = iter[i];
//         else if (iter[i] == '>' && iter[i] && iter[i + 1] == '>')
//         {
//             temp[++j] = ' ';
//             temp[++j] = '>';
//             temp[++j] = '>';
//             temp[++j] = ' ';
//             i += 2;
//             continue ;
//         }
//         else if (iter[i] == '<' && iter[i] && iter[i + 1] == '<')
//         {
//              temp[++j] = ' ';
//             temp[++j] = '<';
//             temp[++j] = '<';
//             temp[++j] = ' ';
//             i += 2;
//             continue ;
//         }
//         i++;
//     }
    
//     free(iter);
//     *str = temp;
// }

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
        if (iter[i] == '\"' || iter[i] == '\'')
        {
            i++;
            while (iter[i] && (iter[i] != '\"' || iter[i] != '\''))
                temp[++j] = iter[i++];
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
    free(*str);
    *str = temp;
}


// void    remove_empty_quotes(char *str)
// {
//     int len;
//     int i;

//     i = 0;
//     len = ft_strlen(str) - 1;
//     while (str[i])
//     {
//         if (str[i] == '\"')
//         {
            
//         }
//     }
// }

// void    shift_to_left(char *str)
// {

// }

void    add_space_to_redirec(t_minishell *ptr)
{
    int i;
    
    i = 0;
    while (ptr->splited_pipe[i])
    {
        if (is_there_heredoc(ptr->splited_pipe[i]) != 0 ||
            is_there_append(ptr->splited_pipe[i]) != 0)
            add_space_double(&ptr->splited_pipe[i]);
        if (is_there_in_redirection(ptr->splited_pipe[i]) != 0 ||
            is_there_out_redirection(ptr->splited_pipe[i]) != 0)
            add_space_one(&ptr->splited_pipe[i]);
        i++;
    }
}

void    remove_quotes(t_minishell *ptr, char *str)
{
    // char *temp;
    int i;
    int j;

    i = 0;
    j = 0;
    // len = ft_strlen(str);
    fill_sapce_with(str, ';'); // fill spaces inside double or singl quotes
    ptr->splited_space = ft_split(str, ' ');
    while (ptr->splited_space[j])
    {
        printf("==>%s\n", ptr->splited_space[j]);
        j++;
    }
    printf("-------------------------------------------\n");
    // while (ptr->splited_space[i])
    // {
    // }
}


void    handle_quotes(t_minishell *ptr)
{
    int count_double_q;
    int count_singl_q;
    int i;

    if(check_is_quotes_close(ptr) == 1)
        ft_perror("Error : Sysntax Error\n", 1);
    add_space_to_redirec(ptr);
    i = 0;
    while (ptr->splited_pipe[i])
    {
        printf("-- before : %s\n", ptr->splited_pipe[i]);
        count_double_q = count_double_quotes(ptr->splited_pipe[i]);
        count_singl_q = count_singl_quotes(ptr->splited_pipe[i]);
        remove_quotes(ptr, ptr->splited_pipe[i]);
        i++;
    }
}