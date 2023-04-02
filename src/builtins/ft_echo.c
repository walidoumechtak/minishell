/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:30:35 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/30 10:32:19by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *arg)
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
	int	flag[2];

	flag[0] = 1;
	flag[1] = 1;
	if (*args)
	{
		while (args && *args)
		{
			if (flag[1] && check_flag(*args))
			{
				flag[0] = 0;
				args++;
				continue ;
			}
			flag[1] = 0;
			printf("%s", *args);
			args++;
			if (args && *args)
				printf(" ");
		}
	}
	if (flag[0])
		printf("\n");
	return (0);
}
