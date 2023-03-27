#include "minishell.h"


static  void    dollar_case(char *iter, int *i, int *s, int *e)
{
    *s = *i;
    while (iter[++*i] && iter[*i] == '$')
        ;
    if (iter[*i] == '?')
        *e = *i++ - *s + 1;
    else if (iter[*i] == '\0')
        *e = *i++ - *s;
    else
    {
        while(((iter[*i] >= 'a' && iter[*i] <= 'z')
        || (iter[*i] >= 'A' && iter[*i] <= 'Z')
        || (iter[*i] >= '0' && iter[*i] <= '9')) && iter[*i] != '\0')
            (*i)++;
        *e = *i - *s;
    }
}

static  void    exp_result(t_minishell *ptr, char *sub, char **res)
{
    char    *temp;

    temp = NULL;
    if (ft_strnstr(sub, "$?", ft_strlen(sub))) // ptr, sub, temp, res
        expaind_exit_state(ptr, &sub);
    if (ft_strchr(sub, '$') != NULL) 
        ft_coted_exapaind(ptr, &sub);
    temp = ft_strjoin(temp, sub);
    free(sub);
    free(*res);
    *res = temp;
}

/**
 * exaind_heredoc - exaind every variable inside heredoc if the limiter has no quotes
*/

void    expaind_heredoc(t_minishell *ptr, char **str)
{
    char    *res;
    char    *iter;
    char    *sub;
    int i;
    int s;
    int e;

    iter = *str;
    i = 0;
    res = NULL;
    while (iter[i])
    {
        if (iter[i] == '$')
            dollar_case(iter, &i, &s, &e);
        else
        {
            s = i;
            while (iter[++i] && iter[i] != '$')
                ;
            e = i - s;       
        }
        sub = ft_substr(iter, s, e);
        exp_result(ptr, sub, &res);
    }
    *str = res;
}