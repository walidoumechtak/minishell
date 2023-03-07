#include "minishell.h"

static	int is_builtins(char *cmd)
{
	if (ft_strnstr(cmd, "echo", ft_strlen(cmd)))
		return (1);
	else if (ft_strnstr(cmd, "unset", ft_strlen(cmd)))
		return (2);
	else if (ft_strnstr(cmd, "export", ft_strlen(cmd)))
		return (3);
	else if (ft_strnstr(cmd, "cd", ft_strlen(cmd)))
		return (4);
	else if (ft_strnstr(cmd, "env", ft_strlen(cmd)))
		return (5);
	else if (ft_strnstr(cmd, "exit", ft_strlen(cmd)))
		return (6);
	return (0);
}
void	ft_exec(t_minishell *shell)
{
	int tmp;
	
	tmp = 0;
	if (ft_lstsize(shell->list_cmd) != 1)
	{
		tmp = is_builtins(*((t_cmd *)(shell->list_cmd->content))->cmd);
		if (tmp != 0)
		{
			if (tmp == 1)
				ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
			// else if (tmp == 2)
			// 	ft_unset(++((t_cmd *)(shell->list_cmd->content))->cmd);
			// else if (tmp == 3)
			// 	ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
			// else if (tmp == 4)
			// 	ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
			// else if (tmp == 5)
			// 	ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
			// else if (tmp == 6)
			// 	ft_echo(++((t_cmd *)(shell->list_cmd->content))->cmd);
		}
	}
	else
		ft_pipe(shell);

}
int main(void)
{	
	t_minishell shell;
	t_cmd	*cmd;

	//shell = (t_minishell *)malloc(sizeof(t_minishell));
	char *ar[] = {"/bin/echo", "-n", "'hello'", NULL};

	shell.list_cmd = NULL;
	cmd = (t_cmd *)malloc(sizeof(cmd));
	cmd->cmd = ar;
	cmd->fd_in = 0;
	cmd->fd_out = 1;

	ft_lstadd_back(&shell.list_cmd, ft_lstnew(cmd));
	char *arv[] = {"/usr/bin/wc",NULL};

	shell.list_cmd = NULL;
	cmd = (t_cmd *)malloc(sizeof(cmd));
	cmd->cmd = arv;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	ft_lstadd_back(&shell.list_cmd, ft_lstnew(cmd));
	ft_exec(&shell);
}