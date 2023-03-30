/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:43:30 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/30 10:59:39 by hbenfadd         ###   ########.fr       */
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

int	ft_export(t_minishell *shell, char **args)
{
	char	**temp;

	temp = (char **)malloc(sizeof(char *) * 2);
	temp[1] = NULL;
	if (!args || !*args)
		ft_putenv(shell->env);
	while (args && *args)
	{
		if (ft_isdigit(**args) || !ft_isalpha(**args))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			temp[0] = *args;
			add_to_env(shell, temp);
		}
		args++;
	}
	free(temp);
	return (EXIT_SUCCESS);
}
