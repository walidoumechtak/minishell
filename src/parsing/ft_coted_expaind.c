#include "minishell.h"

// return the value with out any split.
int    ft_coted_exapaind(t_minishell *ptr, char **str)
{
    char *temp;
    t_list  *exp;
    int i;
    int s;
    int e;

    i = 0;
    s = i;
    temp = *str;
    exp = ptr->env;
    while (temp[i + 1] || temp[i] != '\'')
        i++;
    e = i;
    while (exp)
    {
        if (ft_strncmp(((t_env *)exp->content)->env_var, temp + 1, ft_strlen(temp + 1)) == 0)
        {
            free(*str);
            *str = ft_strdup(((t_env *)exp->content)->env_value);
            return 0;
        }
        exp = exp->next;
    }
    free(*str);
    *str = ft_calloc(1,1);
    return (0);
}