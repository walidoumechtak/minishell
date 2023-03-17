#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/param.h>
# include <fcntl.h>
# include <sys/wait.h>

# define NONE "\033[0m"
# define GREEN "\033[32m"
# define RED "\033[91m"
# define GRAY "\033[2;37m"
# define ITALIC "\033[3m"

typedef struct s_repare_cmd
{
	char	*result;
	char	*iter;
	char	*temp;
	char	*sub;
	int		i;
	int		s;
	int		e;
}			t_repare_cmd;

typedef struct s_command_v1
{
	char	**cmd;
}			t_cmd_v1;

typedef struct s_command
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
}			t_cmd;

typedef struct s_env
{
	char	*env_var;
	char	*env_value;
}			t_env;

typedef struct s_minishell
{
	t_list	*list_v1;
	t_list	*list_cmd;
	t_list	*env;
	int		exit_state;
	char	*str;
	char	**splited_pipe;
	char	**splited_space;
}			t_minishell;

void	init_struct(t_minishell *ptr);
int		parsing(t_minishell *ptr);

/* =====  parsing  ===== */
int		handle_quotes(t_minishell *ptr);
void	ft_exapaind(t_minishell *ptr, char **str);
void	fill_with(char *str, char old, char c);

int		build_linked_list(t_minishell *ptr);
int		build_list_1(t_minishell *ptr);

int		is_there_in_redirection(char *str);
int		is_there_out_redirection(char *str);
int		is_there_heredoc(char *str);
int		is_there_append(char *str);
t_list	*build_env_list(char **env);

/*  ===== Error function ===== */

int		ft_perror(char *str, int status);

/* =====  Builtins  ===== */
int		ft_echo(char **args);
int		ft_cd(t_minishell *shell, char **args);
int		ft_pipe(t_minishell *shell);
int		ft_env(t_list *env);
int		ft_unset(t_minishell *shell, char **agrs);
int		ft_exit(char **args);
int 	ft_export(t_minishell *shell, char **args);

/* =====  Exec function  ===== */
int		exec_is_builtins(t_minishell *shell, char **args, t_list *env);
void	ft_exec(t_minishell *shell);

/*  ===== free function ===== */
void	free_env(t_list **head);
void	free_spilte(char **str);

#endif
