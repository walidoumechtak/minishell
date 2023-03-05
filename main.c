/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/05 12:49:25 by woumecht         ###   ########.fr       */
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
    ptr->env = env;
    while (1)
    {
            ptr->str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
            state = parsing(ptr);
            if (state != 0)
            {
                ft_perror("Error\n", state);
                continue ;
            }
            add_history(ptr->str); // ==> add to cammand history
            free(ptr->str);
    }
    free(ptr);
}