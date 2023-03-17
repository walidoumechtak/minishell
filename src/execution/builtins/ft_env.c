/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:00:28 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/16 17:53:37 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env)
{
	while (env)
	{
		printf("%s", ((t_env *)env->content)->env_var);
		if (((t_env *)env->content)->env_value)
			printf("=%s",((t_env *)env->content)->env_value);
		printf("\n");
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
