/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:42:51 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/16 08:20:12 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list *get_avr(t_minishell *shell, char *var)
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
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_cd(t_minishell *shell, char **args)
{
	t_list	*tmp;
	t_list	*pwd;
	t_list	*oldpwd;
	char	*buff;

	buff = NULL;
	if (chdir(*args) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(*args);
		exit(EXIT_FAILURE);
	}
	oldpwd = get_avr(shell, "OLDPWD");
	pwd = get_avr(shell, "PWD");
	free(((t_env *)oldpwd->content)->env_value);
	((t_env *)oldpwd->content)->env_value = ((t_env *)pwd->content)->env_value;
	tmp = pwd;
  	((t_env *)pwd->content)->env_value = getcwd(buff, 0);
	return (EXIT_SUCCESS);
}
