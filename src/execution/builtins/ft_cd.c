/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:42:51 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/11 05:54:57 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	if (chdir(*args) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(*args);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}