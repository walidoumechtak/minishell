/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:07:22 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/01 16:00:31 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	appent_env_value(t_minishell *shell, char *var, char *value)
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
			free(var);
			free(value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
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
			free(var);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	add_back_to_env(t_minishell *shell, char *var, char *value)
{
	t_env	*new_env;
	t_list	*new_list;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (ft_putstr_fd("Error: memory allocation\n", 2));
	new_env->env_value = value;
	new_env->env_var = var;
	new_list = ft_lstnew(new_env);
	if (!new_list)
		return (ft_putstr_fd("Error: memory allocation\n", 2));
	ft_lstadd_back(&shell->env, new_list);
}

void	add_to_env(t_minishell *shell, char **arg)
{
	char	*tmp;
	char	*value;
	char	*var;
	size_t	len;

	len = ft_strlen(*arg);
	value = NULL;
	var = NULL;
	tmp = ft_strnstr(*arg, "+=", len);
	if (tmp)
	{
		var = ft_substr(*arg, 0, len - ft_strlen(tmp));
		value = ft_strdup(tmp + 2);
		if (appent_env_value(shell, var, value))
			add_back_to_env(shell, var, value);
	}
	else
	{
		tmp = ft_strnstr(*arg, "=", len);
		var = ft_substr(*arg, 0, len - ft_strlen(tmp));
		value = ft_strdup(++tmp);
		if (is_var_found(shell, var, value) == 0)
			add_back_to_env(shell, var, value);
	}
}
