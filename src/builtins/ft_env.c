/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:00:28 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/23 07:06:00 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env)
{
	while (env)
	{
		printf("%s", ((t_env *)env->content)->env_var);
		if (((t_env *)env->content)->env_value)
			printf("=%s", ((t_env *)env->content)->env_value);
		printf("\n");
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
