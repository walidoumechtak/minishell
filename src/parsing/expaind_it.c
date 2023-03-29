/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expaind_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:53:04 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 16:45:17 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expaind_it(t_minishell *ptr, char **str)
{
	t_list	*exp;
	char	*temp;

	temp = *str;
	exp = ptr->env;
	if (temp[0] == '$' && temp[1] == '\0')
		return ;
	while (exp)
	{
		if (ft_strncmp(((t_env *)exp->content)->env_var, temp + 1,
				ft_strlen(temp + 1)
				+ ft_strlen(((t_env *)exp->content)->env_var)) == 0)
		{
			free(*str);
			*str = ft_strdup(((t_env *)exp->content)->env_value);
			return ;
		}
		exp = exp->next;
	}
	free(*str);
	*str = ft_calloc(1, 1);
}
