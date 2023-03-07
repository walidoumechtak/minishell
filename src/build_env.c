#include "minishell.h"


void    build_env_list(t_minishell *ptr, char **env)
{
    t_env   *env_node;
    t_list *new;
    char **temp;
    int i;

    i = 0;
    ptr->env = NULL;
    while (env[i])
    {
        env_node = malloc(sizeof(t_env));
        if (!env_node)
            return;
        temp = ft_split(env[i], '=');
        env_node->env_var = temp[0];
        env_node->env_value = temp[1];
        new = ft_lstnew(env_node);
        if (!new)
        {
            ft_lstclear(&ptr->env, del);
            return ;
        }
        ft_lstadd_back(&ptr->env, new);
        i++;
    }
}