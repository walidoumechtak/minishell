/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:42:51 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/29 12:34:02 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_oldpwd_to_env(t_minishell *shell)
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
	new = ft_lstnew(new_env);
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

static char	*get_value_of_specific_var(t_list *env, char *var)
{
	char	*env_var;
	char	*env_value;

	env_value = NULL;
	while (env)
	{
		env_var = ((t_env *)env->content)->env_var;
		if (ft_strnstr(env_var, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(env_var))
		{
			env_value = ft_strdup(((t_env *)env->content)->env_value);
			if (!env_value)
				return (ft_puterror("Error :cd", "memory allocation", 1), NULL);
			return (env_value);
		}
		env = env->next;
	}
	return (NULL);
}

static int	change_dir(t_minishell *shell, char *path)
{
	if (!access(path, F_OK))
	{
		if (update_value_var_env(shell, "OLDPWD"))
			return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		return (EXIT_FAILURE);
	}
	if (update_value_var_env(shell, "PWD"))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	ft_cd(t_minishell *shell, char **args)
{
	char	*tmp;

	tmp = NULL;
	if (!(args + 1) || !*(args + 1))
	{
		tmp = get_value_of_specific_var(shell->env, "HOME");
		if (!tmp)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		free(*args);
		*args = tmp;
	}
	else if (!**(++args))
		return (EXIT_SUCCESS);
	else if (args[0][0] == '-' && args[0][1] == '\0')
	{
		tmp = get_value_of_specific_var(shell->env, "OLDPWD");
		if (!tmp)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		free(*args);
		*args = tmp;
	}
	if (change_dir(shell, *args))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
