/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:28:12 by hbenfadd          #+#    #+#             */
/*   Updated: 2022/10/29 18:29:50 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (!(c - set[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	x;
	size_t	y;

	i = 0;
	x = 0;
	y = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && check_set(s1[i], set))
		i++;
	x = i;
	i = ft_strlen(s1);
	while (i > x && check_set(s1[--i], set))
			y++;
	return (ft_substr(s1, x, ft_strlen(s1) - (y + x)));
}
