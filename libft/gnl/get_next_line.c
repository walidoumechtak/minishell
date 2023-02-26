/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:24:05 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/02/24 19:16:14 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*del(char **ptr)
{
	free (*ptr);
	*ptr = (NULL);
	return (NULL);
}

static int	check_new_line(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_line(ssize_t b, char **str, char *buff)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = *str;
	if (!(*str))
		return (NULL);
	while (str[0][i])
	{
		if (str[0][i] == '\n' || (!b && !str[0][i + 1]))
		{
			buff = ft_substr_gnl(*str, 0, i + 1);
			break ;
		}
		i++;
	}
	if (str[0][++i])
	{
		*str = ft_strdup_gnl(*str + i);
		del(&tmp);
	}
	else
		del(str);
	return (buff);
}

static char	*get_read(int fd, char **stptr)
{
	char		*buff;
	char		*tmp;
	ssize_t		b;

	buff = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (1)
	{
		tmp = *stptr;
		b = read(fd, buff, BUFFER_SIZE);
		if (b < 0)
			return (free(buff), del(stptr), NULL);
		buff[b] = '\0';
		if (b)
		{
			*stptr = ft_strjoin_gnl(*stptr, buff);
			del(&tmp);
			if (!(*stptr))
				return (free(buff), NULL);
		}
		if (!b || check_new_line(buff))
			break ;
	}
	return (del(&buff), get_line(b, stptr, buff));
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stptr;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= SIZE_MAX)
		return (NULL);
	line = get_read(fd, &stptr);
	return (line);
}
