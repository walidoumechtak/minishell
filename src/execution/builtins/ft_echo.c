/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:30:35 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/07 08:35:29 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	short int flag;

	flag = 0;	
	if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\0')
	{
		flag = 1;
		args++;
	}
	while (args && *args)
	{
		printf("%s", *args);
		args++;
		if (args && *args)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
