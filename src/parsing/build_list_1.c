#include "minishell.h"

void    repear_cmd(t_minishell *ptr, char **str)
{
    //ft_exapaind(ptr, str);
    t_repare_cmd    *rep;
    rep = malloc(sizeof(t_repare_cmd));
    rep->iter = *str;
    rep->result = NULL;
    rep->sub = NULL;
    rep->i = 0;
    if (!rep->iter)
        return;
    while (rep->iter[rep->i])
    {
        // =======================================================================  frist : handle "
        if (rep->iter[rep->i] == '\"')  
        {
            rep->s = rep->i + 1;
            while (rep->iter[++rep->i] != '\"');
            if (rep->i - rep->s == 0)
                rep->e = 0;
            else
                rep->e = rep->i - rep->s;
            rep->sub = ft_substr(rep->iter, rep->s, rep->e);
            printf("sub : %s\n", rep->sub);
            if (ft_strchr(rep->sub, '$') != NULL && ptr->here_flag == 0)
                ft_coted_exapaind(ptr, &rep->sub);
            if (ft_strnstr(rep->sub, "$?", ft_strlen(rep->sub)))
            {
                //printf("sub exit : %s\n", rep->sub);
                expaind_exit_state(ptr, &rep->sub);
            }
            ptr->here_flag = 0;
            //printf("rep->iter + rep->i : %s\n", rep->sub);
        }
        // ======================================================================== second : handle '
        else if (rep->iter[rep->i] == '\'') 
        {
            //printf("here_flag : %d\n", ptr->here_flag); 
             rep->s = rep->i + 1;
            while (rep->iter[++rep->i] != '\'');
            //printf("diff : %d\n", rep->i - rep->s);
            if (rep->i - rep->s == 0)
                rep->e = 0;
            else
                rep->e = rep->i - rep->s;
             //printf("start : %d end : %d\n", rep->s, rep->e);
            rep->sub = ft_substr(rep->iter, rep->s, rep->e);
            ptr->here_flag = 0;
        }
           // ===================================================================== third : any charactere
        else                             
        {                                        
            if (rep->iter[rep->i] == '$' && rep->iter[rep->i])     // in exapaind $ only become \0.      
            {     
                //printf("here_flag $: %d\n", ptr->here_flag);
                rep->s = rep->i;
                rep->i++;
                while(((rep->iter[rep->i] >= 'a' && rep->iter[rep->i] <= 'z')
                || (rep->iter[rep->i] >= 'A' && rep->iter[rep->i] <= 'Z')
                || (rep->iter[rep->i] >= '0' && rep->iter[rep->i] <= '9')) && rep->iter[rep->i] != '\0')
                    rep->i++;
                if (rep->iter[rep->i] == '?') // $?
                    rep->i++;
                if (rep->iter[rep->i] == '\0')
                    rep->e = rep->i;
                else
                    rep->e = rep->i - rep->s;
                    //rep->e = rep->i - 1;  // $USER.walid  i = . so i-- = R
                //printf("start : %d end : %d\n", rep->s, rep->e);
                rep->sub = ft_substr(rep->iter, rep->s, rep->e);
                if (ptr->here_flag == 0)
                    ft_uncoted_exapaind(ptr, &rep->sub);
                if (ft_strnstr(rep->sub, "$?", ft_strlen(rep->sub)))
                {
                    expaind_exit_state(ptr, &rep->sub);
                }
                if (rep->iter[rep->i] != '\0')
                    rep->i--;
                ptr->here_flag = 0;
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
                if (ft_strncmp(rep->iter, "<<", 2) == 0)
                    ptr->here_flag = 1;
                else
                    ptr->here_flag = 0;
             }
        }           
            // =================================================================== end
        if (rep->iter[rep->i] != '\0')
            rep->i++;
        //printf("sub --> %s\n", rep->sub);
        rep->temp = ft_strjoin(rep->result, rep->sub);
        free(rep->sub);
        free(rep->result);
        rep->result = rep->temp; 
    }
    //printf("-- %s --\n", rep->result);
    free(*str);
    *str = rep->result;
    free(rep);
}


// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========
// -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -======== -========

void    build_flag_redrection(t_cmd_v1 *node_v1,char *str)
{
    char **arr;
    int cpt;
    int j;

    j = 0;
    cpt = 0;
    fill_with(str, '\t', ' ');
    arr = ft_split(str, ' ');
    while (arr[j])
    {
        if (ft_strchr(arr[j], '<') != NULL || ft_strchr(arr[j], '>') != NULL)
            cpt++;
        j++;
    }
    node_v1->flags_red = ft_calloc(cpt, sizeof(int));
    node_v1->cpt_flags = cpt;
    free_spilte(arr);
}

void    build_if_expaind_heredoc(t_cmd_v1 *node_v1, char *str)
{
    char **arr;
    int cpt;
    int j;
    int i;

    j = 0;
    i = 0;
    cpt = 0;
    fill_with(str, '\t', ' ');
    arr = ft_split(str, ' ');
    while (arr[j])
    {
        if (ft_strncmp(arr[j], "<<", ft_strlen(arr[j])) == 0)
            cpt++;
        j++;
    }
    node_v1->expaind_here = ft_calloc(cpt, sizeof(int));
    node_v1->cpt_exp_here = cpt;
    j = 0;
    while (arr[j])
    {
        if (ft_strncmp(arr[j], "<<", ft_strlen(arr[j])) == 0 && (ft_strchr(arr[j + 1], '\"') == NULL && ft_strchr(arr[j + 1], '\'') == NULL))
            node_v1->expaind_here[i++] = 1;
        j++;
    }
    free_spilte(arr);
}

int build_list_1(t_minishell *ptr)
{
    t_cmd_v1    *node_v1;
    t_list *new;
    int k;
    int i;
    int j;

    i = 0;
    j = 0;
    ptr->list_v1 = NULL;
    ptr->here_flag = 0; // to check if the $USER should exapaind or not if there is here_doc exemple : "<<" $USER --> << woumecht
    while (ptr->splited_pipe[i])
    {
        j = 0;
        k = 0;
        node_v1 = malloc(sizeof(t_cmd_v1));
        ptr->splited_space = ft_split(ptr->splited_pipe[i], ' ');
        build_flag_redrection(node_v1, ptr->splited_pipe[i]);
        build_if_expaind_heredoc(node_v1, ptr->splited_pipe[i]);
        while (ptr->splited_space[j])
        {
            fill_with(ptr->splited_space[j], '\t', ' ');
            if ((ft_strchr(ptr->splited_space[j], '<') || ft_strchr(ptr->splited_space[j], '>'))
             && (!(ft_strchr(ptr->splited_space[j], '\"')) && !(ft_strchr(ptr->splited_space[j], '\''))))
             {
                node_v1->flags_red[k++] = 1;
             }
            else if ((ft_strchr(ptr->splited_space[j], '<') || ft_strchr(ptr->splited_space[j], '>')))
            {
                k++;
            }
            /*
                rep_cmd ==> containe expaind and remove ineccerey quotes, all command should be clear
            */
            repear_cmd(ptr, &ptr->splited_space[j]);
            j++;
        }
        node_v1->cmd = ptr->splited_space;
        new = ft_lstnew(node_v1);
        if (!new)
            return (3);
        ft_lstadd_back(&ptr->list_v1, new);
        i++;
    }
    return (0);
}