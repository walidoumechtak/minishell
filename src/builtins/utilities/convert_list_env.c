/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:54:26 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/23 07:31:44 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_list_env(t_list *lstenv)
{
	char	**env;
	size_t	size;
	char	*tmp;
	size_t	i;

	i = 0;
	size = ft_lstsize(lstenv) + 1;
	env = (char **)malloc(sizeof(char *) * size);
	while (lstenv)
	{
		if (((t_env *)lstenv->content)->env_value)
		{
			tmp = ft_strjoin(((t_env *)lstenv->content)->env_var, "=");
			env[i] = ft_strjoin(tmp, ((t_env *)lstenv->content)->env_value);
			if (!tmp || !env[i])
				return (ft_puterror("Error", "memory allocation", 1), NULL);
			free(tmp);
		}
		else
			env[i] = ((t_env *)lstenv->content)->env_var;
		lstenv = lstenv->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
