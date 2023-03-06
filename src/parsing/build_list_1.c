#include "minishell.h"

void    repear_cmd(t_minishell *ptr, char **str)
{
    //ft_exapaind(ptr, str);
    t_repare_cmd    *rep;
    (void)ptr;
    rep = malloc(sizeof(t_repare_cmd));
    rep->iter = *str;
    rep->result = NULL;
    rep->i = 0;
    if (ft_strlen(*str) == 2 && ((*str[0] == '\"' && *str[1] == '\"') || (*str[0] == '\'' && *str[1] == '\'')))
    {
        ft_bzero(*str, ft_strlen(*str));
        free(rep);
        return ;
    }
    while (rep->iter[rep->i])
    {
        // =======================================================================  frist : handle "
        if (rep->iter[rep->i] == '\"')  
        {
            rep->s = rep->i + 1;
            while (rep->iter[++rep->i] != '\"');
            rep->e = rep->i - 1;
            rep->sub = ft_substr(rep->iter, rep->s, rep->e);
            if (ft_strchr(rep->sub, '$') != NULL)
                ft_exapaind(ptr, &rep->sub);
        }
        // ======================================================================== second : handle '
        else if (rep->iter[rep->i] == '\'') 
        {
             rep->s = rep->i + 1;
            while (rep->iter[++rep->i] != '\'');
            rep->e = rep->i - 1;
            rep->sub = ft_substr(rep->iter, rep->s, rep->e);
            if (ft_strchr(rep->sub, '$') != NULL)
                ft_exapaind(ptr, &rep->sub);
        }
           // ===================================================================== thirt : any charactere
        else                             
        {                                        
             if (rep->iter[rep->i] == '$')            
             {                                                                  
                 rep->s = rep->i;
                 rep->i++;
                while((rep->iter[rep->i] >= 'a' && rep->iter[rep->i] <= 'z')
                || (rep->iter[rep->i] >= 'A' && rep->iter[rep->i] <= 'Z')
                || (rep->iter[rep->i] >= '0' && rep->iter[rep->i] <= '9'))
                    rep->i++;
                rep->e = rep->i - 1;  // $USER.walid  i = . so i-- = R
                rep->sub = ft_substr(rep->iter, rep->s, rep->e);
                ft_exapaind(ptr, &rep->sub);
             }
             else
             {
                rep->s = rep->i;
                rep->i++;
                while (rep->iter[rep->i] != '$' || rep->iter[rep->i])
                    rep->i++;
                rep->e = rep->i - 1;
                rep->sub = ft_substr(rep->iter, rep->s, rep->e);
             }
        }           
            // =================================================================== end
        rep->i++;
        rep->temp = ft_strjoin(rep->result, rep->sub);
        free(rep->result);
        rep->result = rep->temp; 
    }
    free(*str);
    *str = rep->result;
}

int build_list_1(t_minishell *ptr)
{
    t_cmd_v1    *node_v1;
    int i;
    int j;

    i = 0;
    j = 0;
    ptr->list_v1 = NULL;
    while (ptr->splited_pipe[i])
    {
        node_v1 = malloc(sizeof(t_cmd_v1));
        ptr->splited_space = ft_split(ptr->splited_pipe[i], ' ');
        while (ptr->splited_space[j++])
        {
            fill_with(ptr->splited_space[j], '\t', ' ');
            /*
                rep_cmd ==> containe expaind and remove ineccerey quotes, all command should be clear
            */
            repear_cmd(ptr, &ptr->splited_space[j]);
        }
        node_v1->cmd = ptr->splited_space;
        ft_lstadd_back(&ptr->list_v1, ft_lstnew(node_v1));
        i++;
    }
    return (0);
}