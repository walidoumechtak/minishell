/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/23 10:02:55 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    all_errors_parsing(t_minishell *ptr, int state)
{
    if (state == 1)
        ft_perror(ptr, "Error : sysntax Error\n", state);
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
            //close(((t_cmd *)ptr->list_cmd->content)->fd_in);
        }
        if (((t_cmd *)ptr->list_cmd->content)->fd_out != 1)
        {
            // free(((t_cmd *)ptr->list_cmd->content)->fd_out);           
            //close(((t_cmd *)ptr->list_cmd->content)->fd_out);
        }
        ptr->list_cmd = ptr->list_cmd->next;
    }
}

void    remove_heredoc_files(t_minishell *ptr)
{
    t_list  *temp1;
    t_list  *temp2;

    temp1 = ptr->list_cmd;
    while (temp1)
    {
        temp2 = ((t_cmd *)temp1->content)->opened_files;
        while (temp2)
        {
            if (((t_open_file *)temp2->content)->mode == 4)
                unlink(((t_open_file *)temp2->content)->file);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

/**
 * signal_handler1 - function that handle the SIGINT signal in the main proccess
*/

void    signal_handler1(int sig)
{
    if (sig == SIGINT)
    {
        free_flag = 1;
        write(STDOUT_FILENO, "\n", 2);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

 int main(int ac, char **av, char **env)
{
    t_minishell *ptr;
    int state;

    (void)av;
    (void)ac;
    ptr = malloc(sizeof(t_minishell));
    free_flag = 0;
    ptr->env = build_env_list(env);
    ptr->exit_state = 0;
    signal(SIGINT, signal_handler1);
    while (1)
    {
        if (free_flag == 1)
        {
            ptr->exit_state = 1;
            free_flag = 0;
            //ptr->str = NULL;
            // free_linked_lists(ptr, 1);
        }
        ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
        add_history(ptr->str); // ==> add to cammand history
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
        else
            ptr->exit_state = 0;
        ft_exec(ptr);
        remove_heredoc_files(ptr);
        free_linked_lists(ptr, 1);
        // close_fd(ptr);
        free(ptr->str);
        free_spilte(ptr->splited_pipe);
    }
    free(ptr);
}