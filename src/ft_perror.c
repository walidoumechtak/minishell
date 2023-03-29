/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:49:20 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 16:49:22 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_perror(t_minishell *ptr, char *str, int status)
{
	ft_putstr_fd(str, 2);
	ptr->exit_state = status;
	return (status);
}
