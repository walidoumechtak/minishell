/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:49:11 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 18:38:14 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define NONE "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[91m"
#define GRAY "\033[2;37m"
#define ITALIC "\033[3m"


typedef struct s_mini
{
    char **cmd;
    char *file;
    
}           t_mini;

/*Builtins*/
int	ft_echo(char **args, char *flag);

#endif