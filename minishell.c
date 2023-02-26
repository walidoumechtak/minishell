/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/25 18:13:42 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *str;

    str = NULL;

    while (1)
    {
        str = readline(RED"Minishell"NONE GREEN"-$ "NONE);
        //minishell();
        add_history(str); // ==> add to cammand history
        printf("%s \n", str);
    }
    free(str);
}
