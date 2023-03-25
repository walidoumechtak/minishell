/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/25 18:22:30 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    all_errors_parsing(t_minishell *ptr, int state)
{
    if (state == 1)
    {
        ft_perror(ptr, "Error : sysntax Error\n", 258);
    }
    else if (state == -9)
        ptr->exit_state = 1;
    else if (state == 7 || state == 8 || state == 126)
    {
        free_linked_lists(ptr, 1);
    }
}

void    close_fd(t_minishell *ptr)
{
    t_list  *temp;

    temp = ptr->list_cmd;
    while (temp)
    {
        if (((t_cmd *)temp->content)->fd_in > 2)
            close(((t_cmd *)temp->content)->fd_in);
        if (((t_cmd *)temp->content)->fd_out > 2)
            close(((t_cmd *)temp->content)->fd_out);
        temp = temp->next;
    }
}

void    remove_heredoc_files(t_minishell *ptr)
{
    t_list  *temp1;
    t_list  *temp2;

    temp1 = ptr->list_cmd;
    if (!temp1)
        return ;
    while (temp1)
    {
        temp2 = ((t_cmd *)temp1->content)->opened_files;
        if (!temp2)
            return ;
        while (temp2)
        {
            if (((t_open_file *)temp2->content)->mode == 4)
            {
                //free(((t_open_file *)temp2->content)->file);
                unlink(((t_open_file *)temp2->content)->file);
            }
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

void end_of_program(t_minishell *ptr)
{
    close_fd(ptr);
    remove_heredoc_files(ptr);
    free_linked_lists(ptr, 1);
    free(ptr->str);
    free_spilte(ptr->splited_pipe);
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
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        signal(SIGINT, signal_handler1);
        ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
        if (ptr->str == NULL || ptr->str[0] == '\0' || ptr->str[0] == '\n')
        {
            free(ptr->str);
            continue ;
        }
        add_history(ptr->str); // ==> add to cammand history
        if (free_flag == 1)
        {
            free_flag = 0;
            ptr->exit_state = 1;
            remove_heredoc_files(ptr);
        }
        init_struct(ptr);
        state = parsing(ptr);
        if (state != 0)
        {
            all_errors_parsing(ptr, state);
            free(ptr->str);
            free_spilte(ptr->splited_pipe);
            continue ;
        }
        else
            ptr->exit_state = 0;
        ft_exec(ptr);
        end_of_program(ptr);
    }
    free(ptr);
}