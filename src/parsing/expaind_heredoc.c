/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expaind_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:44:03 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/05 07:23:54 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_expaind_heredoc
{
	char	*res;
	char	*iter;
	char	*sub;
	char	*temp;
	int		i;
	int		s;
	int		e;
}			t_expaind_heredoc;

static void	dollar_case(char *iter, int *i, int *s, int *e)
{
	*s = *i;
	while (iter[++*i] && iter[*i] == '$')
		;
	if (iter[*i] == '?')
		*e = *i++ - *s + 1;
	else if (iter[*i] == '\0')
		*e = *i - *s;
	else
	{
		while (((iter[*i] >= 'a' && iter[*i] <= 'z') || (iter[*i] >= 'A'
					&& iter[*i] <= 'Z') || (iter[*i] >= '0' && iter[*i] <= '9'))
			&& iter[*i] != '\0')
			(*i)++;
		*e = *i - *s;
	}
}

static void	exp_result(t_minishell *ptr, char *sub, char **res, char **temp)
{
	if (ft_strnstr(sub, "$?", ft_strlen(sub)))
		expaind_exit_state(ptr, &sub);
	if (ft_strchr(sub, '$') != NULL)
		ft_coted_exapaind(ptr, &sub);
	*temp = ft_strjoin(*temp, sub);
	free(sub);
	free(*res);
	*res = *temp;
}

/**
 * exaind_heredoc
	- exaind every variable inside heredoc if the limiter has no quotes
*/

void	expaind_heredoc(t_minishell *ptr, char **str)
{
	t_expaind_heredoc	*exp;

	exp = malloc(sizeof(t_expaind_heredoc));
	exp->iter = *str;
	exp->i = 0;
	exp->res = NULL;
	exp->temp = NULL;
	while (exp->iter[exp->i])
	{
		if (exp->iter[exp->i] == '$')
			dollar_case(exp->iter, &exp->i, &exp->s, &exp->e);
		else
		{
			exp->s = exp->i;
			while (exp->iter[++exp->i] && exp->iter[exp->i] != '$')
				;
			exp->e = exp->i - exp->s;
		}
		exp->sub = ft_substr(exp->iter, exp->s, exp->e);
		exp_result(ptr, exp->sub, &exp->res, &exp->temp);
	}
	free(*str);
	*str = exp->res;
	free(exp);
}
