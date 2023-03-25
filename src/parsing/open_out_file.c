#include "minishell.h"

int	open_out_file(t_open_file *link2)
{
	int	fd;

	fd = 1;
	if (link2->mode == 2)
	{
		if (ft_strncmp(link2->file, "/dev/stdin", ft_strlen(link2->file)) == 0
			|| ft_strncmp(link2->file, "/dev/stdout",
				ft_strlen(link2->file)) == 0)
			fd = 1;
		else
			fd = open(link2->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	else if (link2->mode == 3)
	{
		if (ft_strncmp(link2->file, "/dev/stdin", ft_strlen(link2->file)) == 0
			|| ft_strncmp(link2->file, "/dev/stdout",
				ft_strlen(link2->file)) == 0)
			fd = 1;
		else
			fd = open(link2->file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	return (fd);
}