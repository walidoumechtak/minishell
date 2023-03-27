/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:08:01 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/27 11:47:59 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

static char	*get_value_of_path(t_list *env)
{
	char	**buff;

	buff = NULL;
	while (env)
	{
		if (ft_strnstr(((t_env *)env->content)->env_var, "PATH", 4))
			return (((t_env *)env->content)->env_value);
		env = env->next;
	}
	return (NULL);
}

static char	*check_cmd_with_path(char *cmd, char *path)
{
	char	*tmp;
	int		i;
	int		start;
	int		len_cmd;

	start = 0;
	i = 0;	ft_strlcpy(tmp, path + start, i - start);
				ft_strlcat(tmp, cmd, (i - start) + len_cmd)
	len_cmd = ft_strlen(cmd);
	if (!cmd || !*cmd)
		return (ft_putstr_fd("Error: memory allocation\n", 2), exit(1), NULL);
	while (path[i])
	{
		if (path[i++] == ':')
		{
			if (start == i - 1)
				tmp = ft_strjoin(".", cmd);
			else
			{
				tmp = (char *)malloc(sizeof(char) * ((i - start) + len_cmd));
				if (!tmp)
					return (ft_putstr_fd("Error: memory allocation\n", 2), exit(1), NULL);
				ft_strlcpy(tmp, path + start, i - start);
				ft_strlcat(tmp, cmd, (i - start) + len_cmd);
			}
			if (!tmp)
				return (ft_puterror("Error", "memory allocation", 1), NULL);
			if (!access(tmp, F_OK))
			{
				if (!access(tmp, X_OK))
					return (tmp);
				else
					return (ft_puterror(&cmd[1], "permission denied", 1), NULL);
			}
			free(tmp);
			start = i;
		}
	}
	return (ft_puterror(&cmd[1], "command not found", 127), NULL);
}

char	*check_cmd(char *cmd, t_list *env)
{
	if (!ft_isalpha(*cmd))
	{
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (cmd);
			else
				ft_puterror(cmd, "permission denied\n", 1);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			if (cmd[0] != '.' && cmd[0] != '/')
				ft_putstr_fd(": command not found\n", 2);
			else
				ft_putstr_fd(": no such file or directory\n", 2);
			exit(127);
		}
	}
	return (check_cmd_with_path(ft_strjoin("/", cmd), get_value_of_path(env)));
}
