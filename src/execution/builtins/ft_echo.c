/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:30:35 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/23 06:31:42by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_flag(char *arg)
{

	int	i;

	i = 1;
	while (arg[0] == '-' && arg[i] == 'n')
	{
		if (arg[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **args)
{
	int	flag;

	flag = 1;	
	if (*args)
	{
		if (check_flag(*args))
		{
			flag = 0;
			args++;
		}
		while (args && *args)
		{

			printf("%s", *args);
			args++;
			if (args && *args)
				printf(" ");
		}
	}
	if (flag)
		printf("\n");
	return (0);
}
