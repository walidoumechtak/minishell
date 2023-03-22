#include "minishell.h"


static void	free_env(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		free(((t_env *)(tmp->content))->env_value);
		free(((t_env *)(tmp->content))->env_var);
		tmp = tmp->next;
	}
	ft_lstclear(head, del);
}

t_list	*build_env_list(char **env)
{
	t_env	*env_node;
	t_list	*new;
	t_list	*head;
	char	**temp;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		env_node = malloc(sizeof(t_env));
		if (!env_node)
			return (free_env(&head), NULL);
		temp = ft_split(env[i], '=');
		if (!temp)
			return (free_env(&head), NULL);
		env_node->env_var = temp[0];
		env_node->env_value = temp[1];
		new = ft_lstnew(env_node);
		if (!new)
			return (free_env(&head), NULL);
		ft_lstadd_back(&head, new);
		i++;
		free(temp);
	}
	return (head);
}