/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/28 16:04:38 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    t_minishell *ptr;
    int state;

    (void)av;
    (void)ac;
    ptr = malloc(sizeof(t_minishell));
    if (!ptr)
    {
        ft_putstr_fd("Failed to alloc memory\n", 2);
        exit (404);
    }
    g_free_flag = 0;
    ptr->env = build_env_list(env);
    ptr->exit_state = 0;
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        signal(SIGINT, signal_handler1);
        ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
        
        if (ptr->str == NULL || ptr->str[0] == '\0' || ptr->str[0] == '\n')
        {
            if (ptr->str == NULL)
                break ;
            free(ptr->str);
            continue ;
        }
        add_history(ptr->str); // ==> add to cammand history
        if (g_free_flag == 1)
        {
            g_free_flag = 0;
            ptr->exit_state = 1;
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