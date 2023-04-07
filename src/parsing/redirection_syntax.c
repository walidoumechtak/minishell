/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:25:05 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/07 14:14:14 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_rederction(char **split, int j)
{
	int	k;
	int	cpt;

	k = 0;
	cpt = 0;
	if (ft_strncmp(split[j], ">", 1) == 0)
	{
		while (split[j][k] == '>')
		{
			cpt++;
			k++;
		}
	}
	else if (ft_strncmp(split[j], "<", 1) == 0)
	{
		while (split[j][k] == '<')
		{
			cpt++;
			k++;
		}
	}
	if (cpt > 2)
		return (1);
	return (0);
}

int	redirection_null(char **split, int j)
{
	if (ft_strncmp(split[j], ">", ft_strlen(split[j])) == 0
		|| ft_strncmp(split[j], "<", ft_strlen(split[j])) == 0
		|| ft_strncmp(split[j], ">>", ft_strlen(split[j])) == 0
		|| ft_strncmp(split[j], "<<", ft_strlen(split[j])) == 0)
	{
		if (split[j + 1] == NULL)
			return (1);
	}
	return (0);
}

/**
 * first case : if there is null after < or > 
 * second case : if there is redirection symbole after < of >
 * thirt case : if there is >>>... or <<<...
*/

int	rederction_syntax(char *arr)
{
	char	**split;
	int		j;

	j = 0;
	split = ft_split(arr, ' ');
	while (split[j])
	{
		if (redirection_null(split, j) == 1)
			return (free_spilte(split), 1);
		if (split[j + 1] && ((ft_strncmp(split[j], ">", 1) == 0
					|| ft_strncmp(split[j], "<", 1) == 0) && (ft_strncmp(split[j
							+ 1], ">", 1) == 0 || ft_strncmp(split[j + 1], "<",
						1) == 0)))
			return (free_spilte(split), 1);
		else if (count_rederction(split, j) == 1)
			return (free_spilte(split), 1);
		j++;
	}
	return (free_spilte(split), 0);
}
