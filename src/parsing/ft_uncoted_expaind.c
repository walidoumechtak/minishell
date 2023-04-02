/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uncoted_expaind.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 08:57:37 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/02 11:14:59 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_uncoted_expaind
{
	char	**split_var;
	char	*temp;
	char	*temp2;
	char	*res;
	int		i;
	t_list	*exp;
}			t_uncoted_expaind;

void	init_st(t_minishell *ptr, char **str, t_uncoted_expaind *u_e)
{
	u_e->temp = *str;
	u_e->exp = ptr->env;
	u_e->res = NULL;
	u_e->split_var = NULL;
	u_e->i = 0;
}

void	body_u_e(t_uncoted_expaind *u_e, char **str)
{
	u_e->split_var = ft_split(((t_env *)u_e->exp->content)->env_value,
			' ');
	while (u_e->split_var[u_e->i])
	{
		u_e->temp2 = ft_strjoin(u_e->res,
				u_e->split_var[u_e->i]);
		free(u_e->res);
		u_e->res = u_e->temp2;
		if (u_e->split_var[u_e->i + 1] != NULL)
		{
			u_e->temp2 = ft_strjoin(u_e->res, " ");
			free(u_e->res);
			u_e->res = u_e->temp2;
		}
		u_e->i++;
	}
	free(*str);
	free_spilte(u_e->split_var);
	fill_with2(&u_e->res, ' ', '\b');
	*str = u_e->res;
}

int	ft_uncoted_exapaind(t_minishell *ptr, char **str)
{
	t_uncoted_expaind	*u_e;

	u_e = malloc(sizeof(t_uncoted_expaind));
	init_st(ptr, str, u_e);
	if (u_e->temp[0] == '\0' || (u_e->temp[0] && u_e->temp[1] == '\0'))
		return (free(u_e), 0);
	if (u_e->temp[0] == '$' && u_e->temp[1] == '?')
		return (free(u_e), 0);
	while (u_e->exp && u_e->temp[1])
	{
		if (ft_strncmp(((t_env *)u_e->exp->content)->env_var, u_e->temp + 1,
				ft_strlen(u_e->temp + 1)
				+ ft_strlen(((t_env *)u_e->exp->content)->env_var)) == 0)
		{
			body_u_e(u_e, str);
			return (free(u_e), 0);
		}
		u_e->exp = u_e->exp->next;
	}
	free(*str);
	free_spilte(u_e->split_var);
	*str = ft_calloc(2, 1);
	*str[0] = '\b';
	return (free(u_e), 0);
}
