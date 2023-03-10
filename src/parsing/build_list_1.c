#include "minishell.h"

void    repear_cmd(t_minishell *ptr, char **str)
{
    //ft_exapaind(ptr, str);
    t_repare_cmd    *rep;
    (void)ptr;
    rep = malloc(sizeof(t_repare_cmd));
    rep->iter = *str;
    rep->result = NULL;
    rep->sub = NULL;
    rep->i = 0;
    if (!rep->iter)
    {
        printf("www\n");
        return;
    }
    while (rep->iter[rep->i])
    {
        // =======================================================================  frist : handle "
        if (rep->iter[rep->i] == '\"')  
        {

            rep->s = rep->i + 1;
            while (rep->iter[++rep->i] != '\"');
            //printf("diff : %d\n", rep->i - rep->s);
            if (rep->i - rep->s == 0)
                rep->e = 0;
            else
                rep->e = rep->i - rep->s;
            printf("start : %d end : %d\n", rep->s, rep->e);
            rep->sub = ft_substr(rep->iter, rep->s, rep->e);
            if (ft_strchr(rep->sub, '$') != NULL)
                ft_coted_exapaind(ptr, &rep->sub);
        }
        // ======================================================================== second : handle '
        else if (rep->iter[rep->i] == '\'') 
        {
             rep->s = rep->i + 1;
            while (rep->iter[++rep->i] != '\'');
            //printf("diff : %d\n", rep->i - rep->s);
            if (rep->i - rep->s == 0)
                rep->e = 0;
            else
                rep->e = rep->i - rep->s;
             //printf("start : %d end : %d\n", rep->s, rep->e);
            rep->sub = ft_substr(rep->iter, rep->s, rep->e);
        }
           // ===================================================================== third : any charactere
        else                             
        {                                        
             if (rep->iter[rep->i] == '$' && rep->iter[rep->i])     // in exapaind $ only become \0.      
             {                                                                  
                 rep->s = rep->i;
                 rep->i++;
                while(((rep->iter[rep->i] >= 'a' && rep->iter[rep->i] <= 'z')
                || (rep->iter[rep->i] >= 'A' && rep->iter[rep->i] <= 'Z')
                || (rep->iter[rep->i] >= '0' && rep->iter[rep->i] <= '9')) && rep->iter[rep->i] != '\0')
                    rep->i++;
                if (rep->iter[rep->i] == '\0')
                    rep->e = rep->i;
                else
                    rep->e = rep->i - rep->s;
                    //rep->e = rep->i - 1;  // $USER.walid  i = . so i-- = R
                printf("start : %d end : %d\n", rep->s, rep->e);
                rep->sub = ft_substr(rep->iter, rep->s, rep->e);
                // if (rep->sub[0] == '$' && rep->sub[1] == '\0') // ====> $"wa" = wa
                //     rep->sub[0] = '\0';
                // else
                ft_uncoted_exapaind(ptr, &rep->sub);
                if (rep->iter[rep->i] != '\0')
                    rep->i--;
             }
             else
             {
                rep->s = rep->i;
                rep->i++;
                while (rep->iter[rep->i] != '$' && rep->iter[rep->i] != '\"' && rep->iter[rep->i] != '\'' && rep->iter[rep->i])
                    rep->i++;
                if (rep->iter[rep->i] == '\0')
                    rep->e = rep->i;
                else
                    rep->e = rep->i - rep->s;
                //printf("start : %d end : %d\n", rep->s, rep->e);
                rep->sub = ft_substr(rep->iter, rep->s, rep->e);
                if (rep->iter[rep->i] != '\0')
                    rep->i--;
             }
        }           
            // =================================================================== end
        if (rep->iter[rep->i] != '\0')
            rep->i++;
        //printf("sub --> %s\n", rep->sub);
        rep->temp = ft_strjoin(rep->result, rep->sub);
        free(rep->result);
        rep->result = rep->temp; 
    }
    //printf("-- %s --\n", rep->result);
    free(*str);
    *str = rep->result;
}


// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========

int    build_flag_redrection(t_minishell *ptr)
{
    char **arr_s;
    int cpt;
    int i;
    int j;

    i = 0;
    cpt = 0;
    while (ptr->splited_pipe[i])
    {
        arr_s = ft_split(ptr->splited_pipe[i], ' ');
        j = 0;
        while (arr_s[j])
        {
            if (ft_strchr(arr_s[j], '<') != NULL || ft_strchr(arr_s[j], '>') != NULL)
                cpt++;
            j++;
        }
        i++;
    }
    ptr->flags_red = ft_calloc(cpt, sizeof(int));
    return (cpt);
}

int build_list_1(t_minishell *ptr)
{
    t_cmd_v1    *node_v1;
    int cpt;
    int k;
    int i;
    int j;

    i = 0;
    k = 0;
    ptr->list_v1 = NULL;
    cpt = build_flag_redrection(ptr);
    while (ptr->splited_pipe[i])
    {
        j = 0;
        node_v1 = malloc(sizeof(t_cmd_v1));
        ptr->splited_space = ft_split(ptr->splited_pipe[i], ' ');
        while (ptr->splited_space[j])
        {
            fill_with(ptr->splited_space[j], '\t', ' ');
            if ((ft_strchr(ptr->splited_space[j], '<') || ft_strchr(ptr->splited_space[j], '>'))
             && !(ft_strchr(ptr->splited_space[j], '\"')) && !(ft_strchr(ptr->splited_space[j], '\'')))
                ptr->flags_red[k++] = 1;
            else if ((ft_strchr(ptr->splited_space[j], '<') || ft_strchr(ptr->splited_space[j], '>')))
                k++;
            /*
                rep_cmd ==> containe expaind and remove ineccerey quotes, all command should be clear
            */
            repear_cmd(ptr, &ptr->splited_space[j]);
            j++;
        }
        node_v1->cmd = ptr->splited_space;
        ft_lstadd_back(&ptr->list_v1, ft_lstnew(node_v1));
        i++;
    }
    return (0);
}