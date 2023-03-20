/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/20 17:43:38 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    all_errors_parsing(t_minishell *ptr, int state)
{
    if (state == 1)
        ft_perror(ptr, "Error : sysntax Error\n", state);
    else if (state == 126)
        ft_perror(ptr, "bash: /: is a directory\n", state);
    else if (state == -9)
        ptr->exit_state = 1;
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

void free_linked_lists(t_minishell *ptr, int flag)
{
    t_list  *temp1;
    t_list  *temp2;
    t_list  *temp3;
    t_list  *temp4;
    t_cmd *link_ofile;
    
    temp1 = ptr->list_cmd;
    temp2 = ptr->list_v1;
    temp3 = ptr->env;
    while (temp2)
    {
        free(((t_cmd_v1 *)temp2->content)->flags_red);       
        free(((t_cmd_v1 *)temp2->content)->expaind_here);       
        free_spilte(((t_cmd_v1 *)temp2->content)->cmd);
        temp2 = temp2->next;
    }
    ft_lstclear(&ptr->list_v1, del);
    if (flag == 1)
    {
        while (temp1)
        {
            //free_spilte(((t_cmd *)temp1->content)->cmd);
            link_ofile = ((t_cmd *)temp1->content);
            if (link_ofile->fd_out > 2)
                close(link_ofile->fd_out);
            temp4 = link_ofile->opened_files;
            while (link_ofile->opened_files)
            {
                free(((t_open_file *)link_ofile->opened_files->content)->file);
                if (((t_open_file *)link_ofile->opened_files->content)->fd > 2)
                    close(((t_open_file *)link_ofile->opened_files->content)->fd);
                link_ofile->opened_files = link_ofile->opened_files->next;
            }
            ft_lstclear(&temp4, del);
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

// int main(int ac, char **av, char **env)

char    *signal_handler1(int sig)
{
    (void) sig;
    printf("\n");
    return (readline(RED"Minishell"NONE GREEN"-$ "NONE));
}

int main(int ac, char **av)
{
    t_minishell *ptr;
    int state;

    (void)av;
    (void)ac;
    ptr = malloc(sizeof(t_minishell));
    //ptr->env = build_env_list(env);
    ptr->str = (char *) signal(SIGINT, (void *)signal_handler1);
    printf("frome the signal %s\n", ptr->str);
    ptr->exit_state = 0;
    while (1)
    {
            ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
            if (ptr->str == NULL || ptr->str[0] == '\0' || ptr->str[0] == '\n')
            {
                free(ptr->str);
                continue ;
            }
            init_struct(ptr);
            state = parsing(ptr);
            if (state != 0)
            {
                all_errors_parsing(ptr, state);
                //free_linked_lists(ptr, 1);
                free(ptr->str);
                free_spilte(ptr->splited_pipe);
                continue ;
            }
            //ft_exec(ptr);
            add_history(ptr->str); // ==> add to cammand history
            free_linked_lists(ptr, 1);
            close_fd(ptr);
            free(ptr->str);
            free_spilte(ptr->splited_pipe);
    }
    free(ptr);
}