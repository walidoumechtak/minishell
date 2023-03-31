/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_out_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:42:01 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/31 14:28:34 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mode2(t_open_file *link2, int *fd)
{
	if (ft_strncmp(link2->file, "/dev/stdin", ft_strlen(link2->file) + ft_strlen("/dev/stdin")) == 0)
		*fd = 0;
	else if (ft_strncmp(link2->file, "/dev/stdout",
			ft_strlen(link2->file) + ft_strlen("/dev/stdout")) == 0)
		*fd = 1;
	else if (ft_strncmp(link2->file, "/dev/stderr",
			ft_strlen(link2->file) + ft_strlen("/dev/stderr")) == 0)
		*fd = 2;
	else
		*fd = open(link2->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

static void	mode3(t_open_file *link2, int *fd)
{
	if (ft_strncmp(link2->file, "/dev/stdin", ft_strlen(link2->file) + ft_strlen("/dev/stdin")) == 0)
		*fd = 0;
	else if (ft_strncmp(link2->file, "/dev/stdout",
			ft_strlen(link2->file) + ft_strlen("/dev/stdout")) == 0)
		*fd = 1;
	else if (ft_strncmp(link2->file, "/dev/stderr",
			ft_strlen(link2->file) + ft_strlen("/dev/stderr")) == 0)
		*fd = 2;
	else
		*fd = open(link2->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
}

int	open_out_file(t_open_file *link2)
{
	int	fd;

	fd = 1;
	if (link2->mode == 2)
	{
		mode2(link2, &fd);
	}
	else if (link2->mode == 3)
	{
		mode3(link2, &fd);
	}
	return (fd);
}
