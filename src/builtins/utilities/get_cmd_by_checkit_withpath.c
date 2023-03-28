/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_by_checkit_withpath.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:08:01 by hbenfadd          #+#    #+#             */
/*   Updated: 2023/03/27 15:46:24 by hbenfadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_cmd_with_path(char *path, char *cmd, int end)
{
	char		*buff;
	int			len_cmd;
	static int	start;

	len_cmd = ft_strlen(cmd);
	if (start == end - 1)
	{
		buff = ft_strjoin(".", cmd);
		if (!buff)
			return (ft_puterror("Error", "memory allocation", 1), NULL);
	}
	else
	{
		buff = (char *)malloc(sizeof(char) * ((end - start) + len_cmd));
		if (!buff)
			return (ft_puterror("Error", "memory allocation", 1), NULL);
		ft_strlcpy(buff, path + start, end - start);
		ft_strlcat(buff, cmd, (end - start) + len_cmd);
	}
	start = end;
	return (buff);
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
	char	*joined_cmd;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (ft_putstr_fd("Error: memory allocation\n", 2), exit(1), NULL);
	while (path[i])
	{
		if (path[i++] == ':')
		{
			joined_cmd = join_cmd_with_path(path, cmd, i);
			if (!access(joined_cmd, F_OK))
			{
				if (!access(joined_cmd, X_OK))
					return (joined_cmd);
				else
					return (ft_puterror(&cmd[1], "permission denied", 1), NULL);
			}
			free(joined_cmd);
		}
	}
	return (ft_puterror(&cmd[1], "command not found", 127), NULL);
}

char	*get_cmd_by_checkit_withpath(char *cmd, t_list *env)
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
