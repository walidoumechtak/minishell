/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 08:28:51 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/07 10:24:12 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_minishell *shell, char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		exit(shell->exit_state);
	while ((*args)[i])
	{
		if (ft_isalpha((*args)[i]) || (((*args)[++i])
			&& !ft_isdigit((*args)[i])))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	if (args[1])
	{
		ft_putstr_fd("exit\nminishell: exit: too many argument\n", 2);
		return (1);
	}
	exit(ft_atoi(*args));
}
