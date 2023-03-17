/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:32:14 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/17 10:29:34 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*build_env_list(char **env)
{
	t_env	*env_node;
	t_list	*new;
	t_list	*head;
	char	**temp;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		env_node = malloc(sizeof(t_env));
		if (!env_node)
			return (free_env(&head), NULL);
		temp = ft_split(env[i], '=');
		if (!temp)
			return (free_env(&head), NULL);
		env_node->env_var = temp[0];
		env_node->env_value = temp[1];
		new = ft_lstnew(env_node);
		if (!new)
			return (free_env(&head), NULL);
		ft_lstadd_back(&head, new);
		i++;
	}
	return (free(temp), head);
}
