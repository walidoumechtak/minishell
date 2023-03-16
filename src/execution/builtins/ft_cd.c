/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:42:51 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/16 12:36:04 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_avr(t_minishell *shell, char *var)
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
			return ;
		}
		tmp = tmp->next;
	}
}

int	ft_cd(t_minishell *shell, char **args)
{
	get_avr(shell, "OLDPWD");
	if (chdir(*args) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(*args);
		exit(EXIT_FAILURE);
	}
	get_avr(shell, "PWD");
	return (EXIT_SUCCESS);
}
