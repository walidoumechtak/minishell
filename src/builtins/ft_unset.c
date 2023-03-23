/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 06:23:30 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/23 07:34:10 by hbenfadd         ###   ########.fr       */
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

int	ft_unset(t_minishell *shell, char **agrs)
{
	t_list	*tmp;
	char	*env_var;

	tmp = NULL;
	env_var = NULL;
	while (agrs && *agrs)
	{
		tmp = shell->env;
		while (tmp)
		{
			env_var = ((t_env *)tmp->content)->env_var;
			if (ft_strnstr(env_var, *agrs, ft_strlen(*agrs))
				&& ft_strlen(*agrs) == ft_strlen(env_var))
			{
				dell_one_env(shell, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		agrs++;
	}
	return (EXIT_SUCCESS);
}
