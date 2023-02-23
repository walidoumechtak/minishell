/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/23 15:33:56 by woumecht         ###   ########.fr       */
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
        printf("%s \n", str);
    }
    free(str);
}