/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coted_expaind.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:39:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/01 12:06:17 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_coted_expaind
{
	char	*temp;
	char	*res;
	char	*temp_join;
	char	*sub;
	int		i;
	int		s;
	int		e;
}			t_coted_expaind;

void	init_c_e(t_coted_expaind *c_e, char **str)
{
	c_e->i = 0;
	c_e->temp = *str;
	c_e->res = NULL;
}

/**
 * double_dollar_c - function that do this :
 * if we have $$$$4 we skip $$$ and last one past to expaind it
*/

void	double_dollar_c(t_coted_expaind *c_e)
{
	while (c_e->temp[c_e->i] && c_e->temp[c_e->i] == '$')
		c_e->i++;
	c_e->i--;
	c_e->e = c_e->i - c_e->s;
	c_e->sub = ft_substr(c_e->temp, c_e->s, c_e->e);
	c_e->temp_join = ft_strjoin(c_e->res, c_e->sub);
	free(c_e->sub);
	free(c_e->res);
	c_e->res = c_e->temp_join;
}

/**
 * normal_dollar_case - function that normaly expaind the var
*/

void	normal_dollar_case(t_minishell *ptr, t_coted_expaind *c_e)
{
	c_e->s = c_e->i;
	c_e->i++;
	while (c_e->temp[c_e->i] && ((c_e->temp[c_e->i] >= 'a'
				&& c_e->temp[c_e->i] <= 'z') || (c_e->temp[c_e->i] >= 'A'
				&& c_e->temp[c_e->i] <= 'Z') || (c_e->temp[c_e->i] >= '0'
				&& c_e->temp[c_e->i] <= '9') || c_e->temp[c_e->i] == '_'))
	{
		c_e->i++;
	}
	if (c_e->temp[c_e->i] == '\0')
		c_e->e = c_e->i;
	else
		c_e->e = c_e->i - c_e->s;
	c_e->sub = ft_substr(c_e->temp, c_e->s, c_e->e);
	expaind_it(ptr, &c_e->sub);
	c_e->temp_join = ft_strjoin(c_e->res, c_e->sub);
}

/**
 * string_case - function that skip string
 * but we keep this data we don't want to ignore it
*/

void	string_case(t_coted_expaind *c_e)
{
	c_e->s = c_e->i;
	while (c_e->temp[c_e->i] && c_e->temp[c_e->i] != '$')
	{
		c_e->i++;
	}
	if (c_e->temp[c_e->i] == '\0')
		c_e->e = c_e->i;
	else
		c_e->e = c_e->i - c_e->s;
	c_e->sub = ft_substr(c_e->temp, c_e->s, c_e->e);
	c_e->temp_join = ft_strjoin(c_e->res, c_e->sub);
}

int	ft_coted_exapaind(t_minishell *ptr, char **str)
{
	t_coted_expaind	*c_e;

	c_e = malloc(sizeof(t_coted_expaind));
	init_c_e(c_e, str);
	if ((c_e->temp[0] && c_e->temp[1] == '\0') || (c_e->temp[0] == '$'
			&& c_e->temp[1] == '?'))
		return (free(c_e), 0);
	while (c_e->temp[c_e->i])
	{
		if (c_e->temp[c_e->i] == '$')
		{
			c_e->s = c_e->i;
			if (c_e->temp[c_e->i] == '$' && c_e->temp[c_e->i + 1] == '$')
				double_dollar_c(c_e);
			normal_dollar_case(ptr, c_e);
		}
		else
			string_case(c_e);
		free(c_e->res);
		free(c_e->sub);
		c_e->res = c_e->temp_join;
	}
	free(*str);
	*str = c_e->res;
	return (free(c_e), 0);
}
