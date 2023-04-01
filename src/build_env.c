/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:32:14 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/04/01 13:43:31 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_env(t_env *env_node, char *env)
{
	char	*value;
	size_t	len;

	len = ft_strlen(env);
	value = ft_strnstr(env, "=", ft_strlen(env));
	env_node->env_var = ft_substr(env, 0, len - ft_strlen(value));
	env_node->env_value = ft_strdup(++value);
}

t_list	*build_env_list(char **env)
{
	t_env	*env_node;
	t_list	*new;
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		env_node = malloc(sizeof(t_env));
		if (!env_node)
			return (free_env(&head), NULL);
		split_env(env_node, env[i]);
		new = ft_lstnew(env_node);
		if (!new)
			return (free_env(&head), NULL);
		ft_lstadd_back(&head, new);
		i++;
	}
	return (head);
}
