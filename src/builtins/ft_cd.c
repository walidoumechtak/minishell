/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:42:51 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/27 23:14:07by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int add_oldpwd_to_env(t_minishell *shell)
{
	t_env	*new_env;
	char	*buff;
	t_list	*new;

	buff = NULL;
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (ft_putstr_fd("Error: memory allocation\n", 2), 1);
	new_env->env_var = ft_strdup("OLDPWD");
	if (!new_env->env_var)
		return (ft_putstr_fd("Error: memory allocation\n", 2), 1);
	new_env->env_value = getcwd(buff, 0);
	if (!new_env->env_value)
		return (perror("Error"), 1);
	new	= ft_lstnew(new_env);
	if (!new)
		return (ft_putstr_fd("Error: memory allocation\n", 2), 1);
	ft_lstadd_back(&shell->env, new);
	return (0);
}

static int	update_value_var_env(t_minishell *shell, char *var)
{
	t_list	*tmp;
	char	*env_var;
	char	*buff;

	buff = NULL;
	tmp = shell->env;
	while (tmp)
	{
		env_var = ((t_env *)tmp->content)->env_var;
		if (ft_strnstr(env_var, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(env_var))
		{
			free(((t_env *)tmp->content)->env_value);
			((t_env *)tmp->content)->env_value = getcwd(buff, 0);
			if (!(((t_env *)tmp->content)->env_value))
				return (perror("Error"), 1);
			return (0);
		}
		tmp = tmp->next;
	}
	if (ft_strlen(var) == 6)
		return (add_oldpwd_to_env(shell));
	return (0);
}

int	ft_cd(t_minishell *shell, char **args)
{
	if (update_value_var_env(shell, "OLDPWD"))
		return (1);
	if (chdir(*args) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(*args);
		return (EXIT_FAILURE);
	}
	if (update_value_var_env(shell, "PWD"))
		return (1);
	return (EXIT_SUCCESS);
}
