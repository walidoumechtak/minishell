/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:57:07 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 13:40:49 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*ptr;
	t_list	*p;

	if (lst == NULL)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		p = ptr->next;
		free(ptr);
		ptr = p;
	}
	*lst = NULL;
}
