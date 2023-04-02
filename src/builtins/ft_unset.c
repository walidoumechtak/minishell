/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 06:23:30 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/02 12:30:10 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dell_one_env(t_minishell *shell, t_list *lst)
{
	t_list	*tmp;

	tmp = shell->env;
	while (tmp->next != lst)
		tmp = tmp->next;
	if (lst->next)
		tmp->next = lst->next;
	else
		tmp->next = NULL;
	free(((t_env *)lst->content)->env_value);
	free(((t_env *)lst->content)->env_var);
	ft_lstdelone(lst, del);
}

static int	check_varaible(char *var)
{
	int	i;

	i = 0;
	while ((var[i] && var[i] != '=') || var[0] == '=')
	{
		if (var[0] == '-' && var[0] == '\0')
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd("usage: unset [with no options]", 2);
			ft_putstr_fd("[name[=value] ...] or unset\n", 2);
			return (2);
		}
		if (var[i] == '+' && var[i + 1] == '=')
			;
		else if (ft_isdigit(var[0]) || (var[i] != '_' && !ft_isalnum(var[i])))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_minishell *shell, char **args)
{
	t_list	*tmp;
	char	*env_var;
	int		r;

	env_var = NULL;
	while (args && *args)
	{
		r = check_varaible(*args);
		if (r)
			return (r);
		tmp = shell->env;
		while (tmp)
		{
			env_var = ((t_env *)tmp->content)->env_var;
			if (ft_strnstr(env_var, *args, ft_strlen(*args))
				&& ft_strlen(*args) == ft_strlen(env_var))
			{
				dell_one_env(shell, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		args++;
	}
	return (EXIT_SUCCESS);
}
