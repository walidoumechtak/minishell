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
            i++;
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
            i++;
        }
        i++;
    }

}

void    add_space_double(char *str)
{
    char *temp;
    int size;
    int i;
    int j;
    
    i = 0;
    j = 0;
    size = is_there_append(str) + is_there_heredoc(str);
    temp = malloc((ft_strlen(str) + size) * sizeof(char));
    while (str[i])
    {
        if (str[i] != '>' && str[i] != '<')
            temp[j] = str[i];
        else if (str[i] == '>' && str[i] && str[i + 1] == '>')
        {
            temp[j] = ' ';
            temp[++j] = '>';
            temp[++j] = '>';
            temp[++j] = ' ';
            i += 2;
            continue ;
        }
        else if (str[i] == '<' && str[i] && str[i + 1] == '<')
        {
             temp[j] = ' ';
            temp[++j] = '<';
            temp[++j] = '<';
            temp[++j] = ' ';
            i += 2;
            continue ;
        }
        i++;
    }
    free(str);
    str = temp;
}

void    add_space_one(char *str)
{
    char *temp;
    int size;
    int i;
    int j;

    i = 0;
    j = 0;
    size = is_there_in_redirection(str) + is_there_out_redirection(str);
    while (str[i])
    {
        if (str[i] != '>' && str[i] != '<')
            temp[j] = str[i];
        else if (str[i] == '>')
        {
            temp[j] = ' ';
            temp[++j] = '>';
            temp[++j] = ' ';
        }
        else if (str[i] == '<')
        {
            temp[j] = ' ';
            temp[++j] = '<';
            temp[++j] = ' ';
        }
        i++;
    }
    free(str);
    str = temp;
}

void    shift_to_left(char *str)
{
    
}

void    redirection(t_minishell *ptr)
{
    int i;
    
    i = 0;
    while (ptr->splited_space[i])
    {
        if (is_there_heredoc(ptr->splited_space[i]) != 0 ||
            is_there_append(ptr->splited_space[i]) != 0)
            add_space_double(ptr->splited_space[i]);
        if (is_there_in_redirection(ptr->splited_space[i]) != 0 ||
            is_there_out_redirection(ptr->splited_space[i]) != 0)
            add_space_one(ptr->splited_space[i]);
        shift_to_left(ptr->splited_space[i]);
    }
}

void    remove_quotes(t_minishell *ptr, char *str)
{
    char *temp;
    int i;
    int j;

    i = 0;
    // len = ft_strlen(str);
    fill_sapce_with(str, ';'); // fill spaces inside double or singl quotes
    ptr->splited_space = ft_split(str, ' ');
    while (ptr->splited_space[i])
    {
        redirection(ptr);
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
        // ptr->splited_space = ft_split(ptr->splited_pipe[i], ' ');
        remove_quotes(ptr, ptr->splited_pipe[i]);
        
        i++;
    }
}