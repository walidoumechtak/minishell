/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:49:51 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 16:49:53 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_error(t_minishell *ptr, char *file, char *str, int status)
{
	int	i;

	i = 0;
	ft_putstr_fd(file, 2);
	ft_putstr_fd(str, 2);
	ptr->exit_state = status;
}
