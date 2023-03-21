/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:43:30 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/20 18:03:07 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	appent_env_value(t_minishell *shell, char *var, char *value)
{
	t_list	*tmp;
	char	*oldvalue;
	char	*env_var;
	char	*buff;

	buff = NULL;
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

static void	ft_putenv(t_list *env)
{
	while (env)
	{
		printf("declare -x ");
		printf("%s", ((t_env *)env->content)->env_var);
		if (((t_env *)env->content)->env_value)
			printf("=%s", ((t_env *)env->content)->env_value);
		printf("\n");
		env = env->next;
	}
}

static int	is_var_found(t_minishell *shell, char *var, char *value)
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
			((t_env *)tmp->content)->env_value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(t_minishell *shell, char **args)
{
	char	*tmp;
	char	*value;
	char	**split;
	size_t	len;

	tmp = NULL;
	len = 0;
	value = NULL;

	if (!args)
		ft_putenv(shell->env);
	while (args && *args)
	{

		split = ft_split(*args, '=');
		len = ft_strlen(*args);
		value = ft_strnstr(*args, "+=", len);
		if (value)
		{
			tmp = ft_substr(*args, 0, len - ft_strlen(value));
			appent_env_value(shell, tmp, value + 2);
			free(tmp);
		}
		else if (is_var_found(shell, split[0], split[1]) == 0)
		{
			char *ar[2] = {*args, NULL};
			ft_lstadd_back(&shell->env, build_env_list(ar));
			free(split[0]);
			free(split[1]);
		}
		else
			free(split[0]);
		free(split);
		args++;
	}
	return (EXIT_SUCCESS);
}
