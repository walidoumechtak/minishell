/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:41:53 by hbenfadd          #+#    #+#             */
/*   Updated: 2022/10/29 11:39:28 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buff;
	size_t	len;

	if (!s2 || !s1)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	buff = (char *)malloc(len);
	if (!buff)
		return (NULL);
	ft_strlcpy(buff, s1, len);
	ft_strlcat(buff, s2, len);
	return (buff);
}
