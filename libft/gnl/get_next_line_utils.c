/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:31:16 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/02/24 19:16:40 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		len;
	char	*buff;

	len = ft_strlen_gnl(s1);
	buff = (char *)malloc(len + 1);
	if (buff == NULL)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		buff[len] = ((char *)s1)[len];
		len ++;
	}
	buff[len] = 0;
	return (buff);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*buff;
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	buff = (char *)malloc(len);
	if (!buff)
		return (NULL);
	i = ft_strlcpy_gnl(buff, s1, ft_strlen_gnl(s1) + 1);
	while (s2[j])
	{
		buff[i] = s2[j];
		i++;
		j++;
	}
	buff[i] = 0;
	return (buff);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen_gnl(s);
	if (start >= s_len)
		return (ft_strdup_gnl(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy_gnl(substr, s + start, len + 1);
	return (substr);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (ft_strlen_gnl(src));
}
