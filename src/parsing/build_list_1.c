/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:09:57 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/01 14:57:15 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_flag_red_and_reaper(t_minishell *ptr, t_cmd_v1 *node_v1,
		char **splited_space)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (splited_space[j])
	{
		fill_with(splited_space[j], '\b', ' ');
		if ((ft_strchr(splited_space[j], '<') || ft_strchr(splited_space[j],
					'>')) && (!(ft_strchr(splited_space[j], '\"'))
				&& !(ft_strchr(splited_space[j], '\''))))
		{
			node_v1->flags_red[k++] = 1;
		}
		else if ((ft_strchr(splited_space[j], '<')
				|| ft_strchr(splited_space[j], '>')))
		{
			k++;
		}
		reaper_cmd(ptr, &splited_space[j]);
		j++;
	}
}

void	alloc_flag_redrection(t_cmd_v1 *node_v1, char *str)
{
	char	**arr;
	int		cpt;
	int		j;

	j = 0;
	cpt = 0;
	fill_with(str, '\b', ' ');
	arr = ft_split(str, ' ');
	while (arr[j])
	{
		if (ft_strchr(arr[j], '<') != NULL || ft_strchr(arr[j], '>') != NULL)
			cpt++;
		j++;
	}
	node_v1->flags_red = ft_calloc(cpt, sizeof(int));
	node_v1->cpt_flags = cpt;
	free_spilte(arr);
}

void	build_if_expaind_heredoc(t_cmd_v1 *node_v1, char *str, int i)
{
	char	**arr;
	int		cpt;
	int		j;

	j = 0;
	cpt = 0;
	fill_with(str, '\b', ' ');
	arr = ft_split(str, ' ');
	while (arr[j++])
	{
		if (ft_strncmp(arr[j], "<<", ft_strlen(arr[j])) == 0)
			cpt++;
	}
	node_v1->expaind_here = ft_calloc(cpt, sizeof(int));
	node_v1->cpt_exp_here = cpt;
	j = 0;
	while (arr[j])
	{
		if (ft_strncmp(arr[j], "<<", ft_strlen(arr[j])) == 0
			&& (ft_strchr(arr[j + 1], '\"') == NULL
				&& ft_strchr(arr[j + 1], '\'') == NULL))
			node_v1->expaind_here[i++] = 1;
		j++;
	}
	free_spilte(arr);
}

void	failed_malloc(t_minishell *ptr)
{
	free_linked_lists(ptr, 0);
	ft_putstr_fd("Error: memory allocation\n", 2);
	exit(1);
}

/**
 * build_list_1 - function that build the first linked list 
 * here flage is used to check if the $USER should exapaind
 * or not if there is here_doc exemple : "<<" $USER --> << woumecht
*/

int	build_list_1(t_minishell *ptr)
{
	t_cmd_v1	*node_v1;
	t_list		*new;
	int			i;

	i = 0;
	ptr->list_v1 = NULL;
	ptr->here_flag = 0;
	while (ptr->splited_pipe[i])
	{
		node_v1 = malloc(sizeof(t_cmd_v1));
		if (!node_v1)
			failed_malloc(ptr);
		ptr->splited_space = ft_split(ptr->splited_pipe[i], ' ');
		alloc_flag_redrection(node_v1, ptr->splited_pipe[i]);
		build_if_expaind_heredoc(node_v1, ptr->splited_pipe[i], 0);
		ptr->max_here += node_v1->cpt_exp_here;
		build_flag_red_and_reaper(ptr, node_v1, ptr->splited_space);
		node_v1->cmd = ptr->splited_space;
		new = ft_lstnew(node_v1);
		if (!new)
			failed_malloc(ptr);
		ft_lstadd_back(&ptr->list_v1, new);
		i++;
	}
	return (0);
}
