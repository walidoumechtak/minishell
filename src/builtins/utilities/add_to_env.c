/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:07:22 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/23 07:18:17 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	appent_env_value(t_minishell *shell, char *var, char *value)
{
	t_list	*tmp;
	char	*oldvalue;
	char	*env_var;

	oldvalue = NULL;
	tmp = shell->env;
	while (tmp)
	{
		env_var = ((t_env *)tmp->content)->env_var;
		if (ft_strnstr(env_var, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(env_var))
		{
			oldvalue = ((t_env *)tmp->content)->env_value;
			((t_env *)tmp->content)->env_value = ft_strjoin(oldvalue, value);
			free(oldvalue);
			return ;
		}
		tmp = tmp->next;
	}
}

static int	is_var_found(t_minishell *shell, char *var, char *value)
{
	t_list	*tmp;
	char	*env_var;

	tmp = shell->env;
	while (tmp)
	{
		env_var = ((t_env *)tmp->content)->env_var;
		if (ft_strnstr(env_var, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(env_var))
		{
			free(((t_env *)tmp->content)->env_value);
			((t_env *)tmp->content)->env_value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	add_to_env(t_minishell *shell, char **arg)
{
	char	*tmp;
	char	*value;
	char	**split;
	size_t	len;

	split = ft_split(*arg, '=');
	len = ft_strlen(*arg);
	value = ft_strnstr(*arg, "+=", len);
	if (value)
	{
		tmp = ft_substr(*arg, 0, len - ft_strlen(value));
		appent_env_value(shell, tmp, value + 2);
		free(tmp);
	}
	else if (is_var_found(shell, split[0], split[1]) == 0)
	{
		ft_lstadd_back(&shell->env, build_env_list(arg));
		free(split[0]);
		free(split[1]);
	}
	else
		free(split[0]);
	free(split);
}
