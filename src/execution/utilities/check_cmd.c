#include "minishell.h"

static void free_2d(char **ptr)
{
	int i;

	i = 0;
	while(ptr[i])
		free(ptr[i++]);
	free(ptr);
}

static	char **get_path(t_list *env)
{
    char    **buff;

    buff = NULL;
	while (env)
	{
		if (ft_strnstr(((t_env *)env->content)->env_var, "PATH", 4))
        {
			buff = ft_split(((t_env *)env->content)->env_value, ':');
            if (!buff)
            {
                ft_putstr_fd("Error: memory allocation\n", 2);
                exit(1);
            }
            return (buff);
        }
		env = env->next;
	}
	return (NULL);
}

static char *check_cmd_with_path(char *cmd, char **path)
{
	char *tmp;
	int i;

	i = 0;
	if (!(cmd = ft_strjoin("/", cmd)))
		return (ft_putstr_fd("Error: memory allocation\n", 2), exit(1), NULL);
	while (path[i])
	{
		if (!(tmp = ft_strjoin(path[i++], cmd)))
			return (ft_putstr_fd("Error: memory allocation\n", 2), exit(1), NULL);
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
				return (free_2d(path), tmp);
			else
			{
				ft_putstr_fd(&cmd[1], 2);
				ft_putstr_fd(": permission denied\n", 2);
				exit(1);
			}
		}
		free(tmp);
	}
	free_2d(path); 
	return (ft_putstr_fd(&cmd[1], 2), ft_putstr_fd(": command not found\n", 2), exit(127), NULL);
}

char    *check_cmd(char *cmd, t_list *env)
{
	if (!ft_isalpha(*cmd))
	{
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (cmd);
			else
			{
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": permission denied\n", 2);
				exit(1);
			}
		}
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	return (check_cmd_with_path(cmd, get_path(env)));
}
