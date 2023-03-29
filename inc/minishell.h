/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:14:47 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/29 16:47:51 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				g_free_flag;

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

typedef struct s_open_redirection
{
	t_list		*old;
	t_list		*new;
	t_cmd		*new_c;
	t_cmd_v1	*skin;
	int			i;
	int			k;
	int			l;
	int			state;
	int			len;
}				t_open_redirection;

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
char			*get_cmd_by_checkit_withpath(char *cmd, t_list *env);
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
int				open_out_file(t_open_file *link2);
void			reaper_cmd(t_minishell *ptr, char **str);
int				open_heredoc(t_minishell *ptr, char **arr, int i, int is_exp);
int				open_rederiction(t_minishell *ptr, t_list **old_node,
					t_cmd **new_cmd);
void			open_file(t_minishell *ptr, char **arr, int mode, int i);
int				add_space_redirection(char **str);
int				all_cases(t_minishell *ptr, t_open_redirection *o);
void			expaind_it(t_minishell *ptr, char **str);

int				build_linked_list(t_minishell *ptr);
int				build_list_1(t_minishell *ptr);
int				build_list_2(t_minishell *ptr);
int				fill_fd(t_minishell *ptr);

int				is_there_in_red(char *str);
int				is_there_out_red(char *str);
int				is_there_heredoc(char *str);
int				is_there_append(char *str);
t_list			*build_env_list(char **env);

/*  ===== reaper cmd cases ===== */

void			part_double(t_minishell *ptr, t_repare_cmd *rep);
void			part_single(t_minishell *ptr, t_repare_cmd *rep);
void			part_dollar(t_minishell *ptr, t_repare_cmd *rep);
void			part_string(t_minishell *ptr, t_repare_cmd *rep);

/*  ===== main helper ===== */

void			remove_heredoc_files(t_minishell *ptr);
void			all_errors_parsing(t_minishell *ptr, int state);
void			close_fd(t_minishell *ptr);
void			signal_handler1(int sig);
void			end_of_program(t_minishell *ptr);

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
void			free_and_shift(char **arr, int i);

/* ===== readline func ======= */

void			rl_replace_line(const char *text, int clear_undo);

#endif
