/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:15:59 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/25 14:47:39 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	part_double(t_minishell *ptr, t_repare_cmd *rep)
{
	rep->s = rep->i + 1;
	while (rep->iter[++rep->i] != '\"')
		;
	if (rep->i - rep->s == 0)
		rep->e = 0;
	else
		rep->e = rep->i - rep->s;
	rep->sub = ft_substr(rep->iter, rep->s, rep->e);
	if (ft_strchr(rep->sub, '$') != NULL && ptr->here_flag == 0)
		ft_coted_exapaind(ptr, &rep->sub);
	if (ft_strnstr(rep->sub, "$?", ft_strlen(rep->sub)))
		expaind_exit_state(ptr, &rep->sub);
	ptr->here_flag = 0;
}

void	part_single(t_minishell *ptr, t_repare_cmd *rep)
{
	rep->s = rep->i + 1;
	while (rep->iter[++rep->i] != '\'')
		;
	if (rep->i - rep->s == 0)
		rep->e = 0;
	else
		rep->e = rep->i - rep->s;
	rep->sub = ft_substr(rep->iter, rep->s, rep->e);
	ptr->here_flag = 0;
}

void	part_dollar(t_minishell *ptr, t_repare_cmd *rep)
{
	rep->s = rep->i;
	rep->test = rep->s + 1; // to chekc if $ is followed by " or '
	rep->i++;
	while (((rep->iter[rep->i] >= 'a' && rep->iter[rep->i] <= 'z')
			|| (rep->iter[rep->i] >= 'A' && rep->iter[rep->i] <= 'Z')
			|| (rep->iter[rep->i] >= '0' && rep->iter[rep->i] <= '9'))
		&& rep->iter[rep->i] != '\0')
		rep->i++;
	if (rep->iter[rep->i] == '?') // $?
		rep->i++;
	// if (rep->iter[rep->i] == '\0')
	// 	rep->e = rep->i;
	if (rep->iter[rep->test] == '\'' || rep->iter[rep->test] == '\"')
		rep->e = 0;
	else
		rep->e = rep->i - rep->s;
	rep->sub = ft_substr(rep->iter, rep->s, rep->e);
	if (ptr->here_flag == 0)
		ft_uncoted_exapaind(ptr, &rep->sub);
	if (ft_strnstr(rep->sub, "$?", ft_strlen(rep->sub)))
		expaind_exit_state(ptr, &rep->sub);
	if (rep->iter[rep->i] != '\0')
		// this because i increment the loop i++; so if we have $?walid for example i will point to w and i++ will point to a and then i lost 'w'!!!!???
		rep->i--;
	ptr->here_flag = 0;
}

void	part_string(t_minishell *ptr, t_repare_cmd *rep)
{
	rep->s = rep->i;
	rep->i++;
	while (rep->iter[rep->i] != '$' && rep->iter[rep->i] != '\"'
		&& rep->iter[rep->i] != '\'' && rep->iter[rep->i])
		rep->i++;
	// if (rep->iter[rep->i] == '\0')
	// 	rep->e = rep->i;
	// else
	rep->e = rep->i - rep->s;
	rep->sub = ft_substr(rep->iter, rep->s, rep->e);
	if (rep->iter[rep->i] != '\0')
		rep->i--;
	if (ft_strncmp(rep->iter, "<<", 2) == 0)
		ptr->here_flag = 1;
	else
		ptr->here_flag = 0;
}

void	reaper_cmd(t_minishell *ptr, char **str)
{
	t_repare_cmd	*rep;

	rep = malloc(sizeof(t_repare_cmd));
	rep->iter = *str;
	rep->result = NULL;
	rep->sub = NULL;
	rep->i = 0;
	if (!rep->iter)
		return ;
	while (rep->iter[rep->i])
	{
		if (rep->iter[rep->i] == '\"')
			part_double(ptr, rep);
		else if (rep->iter[rep->i] == '\'')
			part_single(ptr, rep);
		else
		{
			if (rep->iter[rep->i] == '$' && rep->iter[rep->i])
				part_dollar(ptr, rep);
			else
                part_string(ptr, rep);
		}
		if (rep->iter[rep->i] != '\0')
			rep->i++;
		rep->temp = ft_strjoin(rep->result, rep->sub);
		free(rep->sub);
		free(rep->result);
		rep->result = rep->temp;
	}
	free(*str);
	*str = rep->result;
	free(rep);
}
