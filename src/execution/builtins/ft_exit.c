/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 08:28:51 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/11 11:41:32 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	while ((*args)[i])
	{
		if (ft_isalpha((*args)[i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
	if (args[1])
	{
		ft_putstr_fd("exit\nminishell: exit: too many argument\n", 2);
		return (1);
	}
	exit(ft_atoi(*args));
}


