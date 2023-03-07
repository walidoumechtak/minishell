/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:00:28 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/07 15:24:56 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env)
{
	while (env)
	{
		printf("%s=%s\n", ((t_env *)env->content)->env_var,
			((t_env *)env->content)->env_value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
