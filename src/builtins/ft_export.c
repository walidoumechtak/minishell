/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:43:30 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/02 10:49:23 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putenv(t_list *env)
{
	while (env)
	{
		printf("declare -x ");
		printf("%s", ((t_env *)env->content)->env_var);
		if (((t_env *)env->content)->env_value)
			printf("=\"%s\"", ((t_env *)env->content)->env_value);
		printf("\n");
		env = env->next;
	}
}

static int	check_varaible(char *var)
{
	int	i;

	i = 0;
	while ((var[i] && var[i] != '=') || var[0] == '=')
	{
		if (var[0] == '-')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd("usage: export [with no options]", 2);
			ft_putstr_fd("[name[=value] ...] or export\n", 2);
			return (2);
		}
		if (var[i] == '+' && var[i + 1] == '=')
			;
		else if (ft_isdigit(var[0]) || (var[i] != '_' && !ft_isalnum(var[i])))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_minishell *shell, char **args)
{
	char	*(temp[2]);
	int		r;

	r = 0;
	temp[1] = NULL;
	if (!args || !*args)
		ft_putenv(shell->env);
	while (args && *args)
	{
		r = check_varaible(*args);
		if (r)
			return (free(temp), r);
		temp[0] = *args;
		add_to_env(shell, temp);
		args++;
	}
	free(temp);
	return (EXIT_SUCCESS);
}
