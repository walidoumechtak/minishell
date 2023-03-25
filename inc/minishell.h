
#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
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
# ifndef FREE_FLAG
#  define FREE_FLAG

int				free_flag;

# endif

/* ===== STRUCT ===== */

typedef struct s_repare_cmd
{
	char		*result;
	char		*iter;
	char		*temp;
	char		*sub;
	int			i;
	int			here_flag;
	int			s;
	int			e;
	int			test;
}				t_repare_cmd;

typedef struct s_command_v1
{
	char		**cmd;
	int			*flags_red;
	int			*expaind_here;
	int			cpt_exp_here;
	int			cpt_flags;
}				t_cmd_v1;

typedef struct s_command
{
	char		**cmd;
	int			fd_in;
	int			fd_out;
	t_list		*opened_files;
}				t_cmd;

typedef struct s_env
{
	char		*env_var;
	char		*env_value;
}				t_env;

typedef struct s_opened_files
{
	char		*file;
	int			fd;
	int			mode;
}				t_open_file;

typedef struct s_minishell
{
	t_list		*list_v1;
	t_list		*list_cmd;
	t_list		*env;
	t_open_file	*o_file;
	t_cmd		*cmd;
	char		*str;
	char		**splited_pipe;
	char		**splited_space;
	int			*flags_red;
	int			here_flag;
	int			exit_state;
	int			out_access;
	int			signal_stop;
}				t_minishell;

/* =====  Builtins  ===== */
int				ft_echo(char **args);
int				ft_cd(t_minishell *shell, char **args);
void			ft_pipe(t_minishell *shell, t_list *cmd);
int				ft_env(t_list *env);
int				ft_unset(t_minishell *shell, char **agrs);
int				ft_exit(char **args);
int				ft_export(t_minishell *shell, char **args);

/* =====  Builtins Utilities ===== */
void			add_to_env(t_minishell *shell, char **arg);
char			*check_cmd(char *cmd, t_list *env);
void			ft_puterror(char *cmd, char *errormsg, int exit_status);

/* =====  Exec function  ===== */
int				exec_is_builtins(t_minishell *shell, char **args, t_list *env);
void			ft_exec(t_minishell *shell);
char			**convert_list_env(t_list *lstenv);

void			init_struct(t_minishell *ptr);
int				parsing(t_minishell *ptr);

/* =====  parsing  ===== */
int				handle_quotes(t_minishell *ptr);
int				ft_uncoted_exapaind(t_minishell *ptr, char **str);
int				ft_coted_exapaind(t_minishell *ptr, char **str);
void			expaind_exit_state(t_minishell *ptr, char **str);
void			expaind_heredoc(t_minishell *ptr, char **str);
void			fill_with(char *str, char old, char c);
int	open_out_file(t_open_file *link2);

int				build_linked_list(t_minishell *ptr);
int				build_list_1(t_minishell *ptr);
int				build_list_2(t_minishell *ptr);

int				is_there_in_redirection(char *str);
int				is_there_out_redirection(char *str);
int				is_there_heredoc(char *str);
int				is_there_append(char *str);
t_list			*build_env_list(char **env);

/*  ===== Error function ===== */
int				check_pipe_2(char *str, int *i);
int				check_pipe_syntax(char *str);
int				check_semi_colum(char **arr);
int				check_backslach(char **arr);
int				check_quotes_close(char **arr);
int				rederction_syntax(char *arr);
int				ft_perror(t_minishell *ptr, char *str, int status);
void			open_error(t_minishell *ptr, char *file, char *str, int status);

/*  ===== free function ===== */

void			free_spilte(char **str);
void			free_linked_lists(t_minishell *ptr, int flag);
void			free_list_v1(t_minishell *ptr, t_list *temp2);
void			free_env(t_list **head);

/* ===== readline func ======= */

void			rl_replace_line(const char *text, int clear_undo);

#endif
