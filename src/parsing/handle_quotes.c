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

void    fill_sapce_with(char *str,char old, char c)
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
                if (str[i] == old)
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
                if (str[i] == old)
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
    size = (is_there_append(*str) + is_there_heredoc(*str) + is_there_in_redirection(*str) + is_there_out_redirection(*str)) * 2;
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
            else
            {
                if (iter[i] == '>')
                {
                    temp[++j] = ' ';
                    while (iter[i] == '>')
                        temp[++j] = iter[i++];
                }
                else if (iter[i] == '<')
                {
                    temp[++j] = ' ';
                    while (iter[i] == '<')
                        temp[++j] = iter[i++];
                    
                }
                i--;
                temp[++j] = ' ';
            }
        }
        i++;
    }
    temp[++j] = '\0';
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





void    remove_quotes(t_minishell *ptr, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    ptr->splited_space = ft_split(str, ' ');
    while (ptr->splited_space[j])
    {
        printf("==>%s\n", ptr->splited_space[j]);
        j++;
    }
    printf("-------------------------------------------\n");
}


void    handle_quotes(t_minishell *ptr)
{
    int i;

    if(check_is_quotes_close(ptr) == 1)
        ft_perror("Error : Sysntax Error\n", 1);
    i = 0;
    while (ptr->splited_pipe[i])
    {
        add_space_double(&ptr->splited_pipe[i]);
        printf("-- before : %s\n", ptr->splited_pipe[i]);
        remove_quotes(ptr, ptr->splited_pipe[i]);
        i++;
    }
}