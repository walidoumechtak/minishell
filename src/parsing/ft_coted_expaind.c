#include "minishell.h"

// return the value with out any split.

void expaind_it(t_minishell *ptr, char **str)
{
    t_list  *exp;
    char *temp;

    temp = *str;
    exp = ptr->env;
    if (temp[0] == '$' && temp[1] == '\0')
        return ;
    while (exp)
    {
        if (ft_strncmp(((t_env *)exp->content)->env_var, temp + 1, ft_strlen(temp + 1) + ft_strlen(((t_env *)exp->content)->env_var)) == 0)
        {
            free(*str);
            *str = ft_strdup(((t_env *)exp->content)->env_value);
            return ;
        }
        exp = exp->next;
    }
    free(*str);
    *str = ft_calloc(1,1);
}

int    ft_coted_exapaind(t_minishell *ptr, char **str)
{
    char *temp;
    char *res;
    char    *temp_join;
    char *sub;
    int i;
    int s;
    int e;

    i = 0;
    temp = *str;
    res = NULL;
    if (temp[0] && temp[1] == '\0')
        return 0;
    if (temp[0] == '$' && temp[1] == '?')
        return (0);
    while (temp[i])
    {
        if (temp[i] == '$')
        {
            s = i;
            if (temp[i] == '$' && temp[i + 1] == '$')
            {
                while (temp[i] && temp[i] == '$') // if we have $$$$ we skip $$$ and last one past to expaind it
                    i++;
                i--;
                e = i;
                sub = ft_substr(temp, s, e);
                temp_join = ft_strjoin(res, sub);
                free(sub);
                free(res);
                res = temp_join; // here end the operation of double $$$$ .....
            }
            s = i;
            i++;
            while (temp[i] && ((temp[i] >= 'a' && temp[i] <= 'z') 
            || (temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= '0' && temp[i] <= '9')))
            {
                i++;
            }
            if (temp[i] == '\0')
                e = i;
            else
                e = i - s;
            sub = ft_substr(temp, s, e);
            expaind_it(ptr, &sub);
        }
        else
        {
            s = i;
            while (temp[i] && temp[i] != '$')
            {
                i++;
            }
            if (temp[i] == '\0')
                e = i;
            else
                e = i - s;
            sub = ft_substr(temp, s, e);
        }
        temp_join = ft_strjoin(res, sub);
        free(res);
        free(sub);
        res = temp_join;
    }
    free(*str);
    *str = res;
    return (0);
}