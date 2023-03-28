/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:30:41 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/28 10:41:52 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_between_red(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[++i] == ' ')
				;
			if (ft_isdigit(str[i]) && (str[i + 1] == '<' || str[i + 1] == '>'))
				return (1);
		}
		if (str[i] != '<' && str[i] != '>')
			i++;
	}
	return (0);
}

int	handle_quotes(t_minishell *ptr)
{
	int	i;

	i = 0;
	while (ptr->splited_pipe[i])
	{
		fill_with(ptr->splited_pipe[i], '\t', '|');
		fill_with(ptr->splited_pipe[i], ' ', '\t');
		if (number_between_red(ptr->splited_pipe[i]) == 1)
			return (1);
		add_space_redirection(&ptr->splited_pipe[i]);
		if (rederction_syntax(ptr->splited_pipe[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
