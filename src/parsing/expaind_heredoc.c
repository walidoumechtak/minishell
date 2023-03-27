#include "minishell.h"

/**
 * exaind_heredoc - exaind every variable inside heredoc if the limiter has no quotes
*/

void    expaind_heredoc(t_minishell *ptr, char **str)
{
    char    *res;
    char    *temp;
    char    *iter;
    char    *sub;
    int i;
    int s;
    int e;

    iter = *str;
    i = 0;
    temp = NULL;
    res = NULL;
    while (iter[i])
    {
        if (iter[i] == '$')
        {
            s = i;
            while (iter[++i] && iter[i] == '$')
                ;
            if (iter[i] == '?')
                e = i++ - s + 1;
            else if (iter[i] == '\0')
                e = i++ - s;
            else
            {
                while(((iter[i] >= 'a' && iter[i] <= 'z')
                || (iter[i] >= 'A' && iter[i] <= 'Z')
                || (iter[i] >= '0' && iter[i] <= '9')) && iter[i] != '\0')
                    i++;
                e = i - s;
            }
        }
        else
        {
            s = i;
            while (iter[++i] && iter[i] != '$')
                ;
            e = i - s;       
        }
        sub = ft_substr(iter, s, e);
        if (ft_strnstr(sub, "$?", ft_strlen(sub)))
            expaind_exit_state(ptr, &sub);
        // if (sub[0] == '\0')
        // {
        //     free(sub);
        //     break ;
        // }
        if (ft_strchr(sub, '$') != NULL) 
            ft_coted_exapaind(ptr, &sub);
        temp = ft_strjoin(temp, sub);
        free(sub);
        free(res);
        res = temp;
        // if (iter[i] != '\0'  && iter[i] != '$')
        //     i++;
    }
    *str = res;
}