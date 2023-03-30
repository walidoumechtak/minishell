/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_with.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:26:48 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 18:25:56 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    fill_with(char *str,char old, char c)
{
    int i;

    if (!str)
        return ;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"' && str[i + 1] != '\0')
        {
            i++;
            while (str[i] && str[i] != '\"')
            {
                if (str[i] == old)
                    str[i] = c;
                i++;
            }
        }
        else if (str[i] == '\'' && str[i + 1] != '\0')
        {
            i++;
            while (str[i] && str[i] != '\'')
            {
                if (str[i] == old)
                    str[i] = c;
                i++;
            }
        }
        i++;
    }
}

// void	fill_with(char *str, char old, char c)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
//         return ;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' && str[i + 1] != '\0')
// 		{
// 			i++;
// 			while (str[i] && str[i++] != '\"')
// 			{
// 				if (str[i] == old)
// 					str[i] = c;
// 			}
// 		}
// 		else if (str[i] == '\'' && str[i + 1] != '\0')
// 		{
// 			i++;
// 			while (str[i] && str[i++] != '\'')
// 			{
// 				if (str[i] == old)
// 					str[i] = c;
// 			}
// 		}
// 		i++;
// 	}
// }
