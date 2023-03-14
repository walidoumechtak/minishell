
#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define NONE "\033[0m"
# define GREEN "\033[32m"
# define RED "\033[91m"
# define GRAY "\033[2;37m"
# define ITALIC "\033[3m"

/* ===== GLOBAL VARIABL ===== */
int			STAT;

/* ===== STRUCT ===== */

typedef struct s_repare_cmd
{
	char	*result;
	char	*iter;
	char	*temp;
	char	*sub;
	int		i;
	int		here_flag;
	int		s;
	int		e;
}			t_repare_cmd;

typedef struct s_command_v1
{
	char	**cmd;
	int		*flags_red;
	int		cpt_flags;
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
	char	*str;
	char	**splited_pipe;
	char	**splited_space;
	int		*flags_red;
	int		here_flag;
	int		exit_state;
}			t_minishell;

void			init_struct(t_minishell *ptr);
int			parsing(t_minishell *ptr);

/* =====  parsing  ===== */
int			handle_quotes(t_minishell *ptr);
int			ft_uncoted_exapaind(t_minishell *ptr, char **str);
int			ft_coted_exapaind(t_minishell *ptr, char **str);
void		fill_with(char *str, char old, char c);

int			build_linked_list(t_minishell *ptr);
int			build_list_1(t_minishell *ptr);

int			is_there_in_redirection(char *str);
int			is_there_out_redirection(char *str);
int			is_there_heredoc(char *str);
int			is_there_append(char *str);
t_list		*build_env_list(char **env);

/*  ===== Error function ===== */

int			ft_perror(t_minishell *ptr ,char *str, int status);

/*  ===== free function ===== */

void		free_spilte(char **str);
#endif