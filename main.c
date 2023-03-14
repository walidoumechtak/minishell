/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/14 17:58:53 by woumecht         ###   ########.fr       */
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
            if (ptr->str == NULL)
                continue ;
            state = parsing(ptr);
            if (state != 0)
            {
                all_errors_parsing(ptr, state);
                free_spilte(ptr->splited_pipe);
                continue ;
            }
            add_history(ptr->str); // ==> add to cammand history
            free(ptr->str);
            free_spilte(ptr->splited_pipe);
    }
    free(ptr);
}