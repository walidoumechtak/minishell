/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/17 18:21:06 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    all_errors_parsing(t_minishell *ptr, int state)
{
    if (state == 1)
        ft_perror(ptr, "Error : sysntax Error\n", state);
    else if (state == 126)
        ft_perror(ptr, "bash: /: is a directory\n", state);
}

void    close_fd(t_minishell *ptr)
{
    while (ptr->list_cmd)
    {
        if (((t_cmd *)ptr->list_cmd->content)->fd_in != 0)
        {
            // free(((t_cmd *)ptr->list_cmd->content)->fd_in);
            close(((t_cmd *)ptr->list_cmd->content)->fd_in);
        }
        if (((t_cmd *)ptr->list_cmd->content)->fd_out != 1)
        {
            // free(((t_cmd *)ptr->list_cmd->content)->fd_out);           
            close(((t_cmd *)ptr->list_cmd->content)->fd_out);
        }
        ptr->list_cmd = ptr->list_cmd->next;
    }
}

void free_lists(t_minishell *ptr, int flag)
{
    t_list  *temp1;
    t_list  *temp2;
    t_list  *temp3;
    
    temp1 = ptr->list_cmd;
    temp2 = ptr->list_v1;
    temp3 = ptr->env;
    while (temp2)
    {
        free(((t_cmd_v1 *)temp2->content)->flags_red);       
        free_spilte(((t_cmd_v1 *)temp2->content)->cmd);
        temp2 = temp2->next;
    }
    ft_lstclear(&ptr->list_v1, del);
    if (flag == 1)
    {
        while (temp1)
        {   
            //free_spilte(((t_cmd *)temp1->content)->cmd);
            temp1 = temp1->next;
        }
        ft_lstclear(&ptr->list_cmd, del);
        // while (temp3)
        // {
        //     free(((t_env*)temp3->content)->env_value);
        //     free(((t_env*)temp3->content)->env_var);
        //     temp3 = temp3->next;
        // }
        // ft_lstclear(&ptr->env, del);
    }
}

int main(int ac, char **av, char **env)
{
    t_minishell *ptr;
    int state;

    (void)av;
    (void)ac;
    ptr = malloc(sizeof(t_minishell));
    ptr->env = build_env_list(env);
    while (1)
    {
            ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
            if (ptr->str == NULL || ptr->str[0] == '\0')
            {
                free(ptr->str);
                continue ;
            }
            init_struct(ptr);
            state = parsing(ptr);
            if (state != 0)
            {
                all_errors_parsing(ptr, state);
                //free_lists(ptr, 0);
                free(ptr->str);
                free_spilte(ptr->splited_pipe);
                continue ;
            }
            //ft_exec(ptr);
            add_history(ptr->str); // ==> add to cammand history
            free_lists(ptr, 1);
            close_fd(ptr);
            free(ptr->str);
            free_spilte(ptr->splited_pipe);
    }
    free(ptr);
}