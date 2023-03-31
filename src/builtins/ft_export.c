/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:43:30 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/30 13:58:22 by woumecht         ###   ########.fr       */
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
	while (var[i] && var[i] != '=')
	{
		if (var[0] == '-')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd("usage: export [with no options]", 2);
			ft_putstr_fd("[name[=value] ...] or export\n", 2);
			return (2);
		}
		if (ft_isdigit(var[i]) || (var[i] != '_' && !ft_isalpha(var[i])))
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
	char	**temp;
	int		r;

	r = 0;
	temp = (char **)malloc(sizeof(char *) * 2);
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
