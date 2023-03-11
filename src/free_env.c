/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 06:27:27 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/11 06:27:43 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		free(((t_env *)(tmp->content))->env_value);
		free(((t_env *)(tmp->content))->env_var);
		tmp = tmp->next;
	}
	ft_lstclear(head, del);
}
