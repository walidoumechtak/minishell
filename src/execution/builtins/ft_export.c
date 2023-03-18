#include "minishell.h"

static void	appent_env_value(t_minishell *shell, char *var, char *value)
{
	t_list	*tmp;
    char    *oldvalue;
	char	*env_var;
	char	*buff;

	buff = NULL;
	oldvalue = NULL;
	tmp = shell->env;
	while (tmp)
	{
		env_var = ((t_env *)tmp->content)->env_var;
		if (ft_strnstr(env_var, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(env_var))
		{
            oldvalue = ((t_env *)tmp->content)->env_value;
			((t_env *)tmp->content)->env_value = ft_strjoin(oldvalue, value);
			free(oldvalue);
			return ;
		}
		tmp = tmp->next;
	}
}

// static char **convert_to_arry(t_list *env)
// {
// 	char	**buff;
// 	t_env	*tmp;
// 	int		i;

// 	i = 0;
// 	buff = ((char **)malloc(sizeof(char *) + 1 ) * ft_lstsize(env));
// 	if (buff)
// 		return (NULL);
//     while (env)
//     {
// 		tmp = env->content;
// 		buff[i] = ft_strjoin(tmp->env_var, tmp->env_value);
//         env = env->next;
//     }
// 	buff[i] = NULL;
// 	return (buff);
// }

// static void	putenv_in_order(t_list *env)
// {
// 	char	**tmp;
// 	int		i = 0;

// 	tmp = convert_to_arry(env);
// 	while ()
// 	{
// 	}

// }

int ft_export(t_minishell *shell, char **args)
{
	char	*tmp;
	char	*value;
	size_t	len;

	tmp = NULL;
	len = 0;
	value = NULL;

    // if (!args)
    //	putenv_in_order(shell->env)
	while (args && *args)
	{
		len = ft_strlen(*args);
		value = ft_strnstr(*args, "+=", len);
		if (value)
		{
			tmp = ft_substr(*args, 0, len - ft_strlen(value));
			appent_env_value(shell, tmp, value + 2);
			free(tmp);
		}
		else
			ft_lstadd_back(&shell->env, build_env_list(args));
		args++;
	}
	return (EXIT_SUCCESS);
}
