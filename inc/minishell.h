
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
typedef struct s_command
{
	char	**cmd;
	char	**redir;
	int		i_pipe;
}			t_cmd;

typedef struct s_mini
{
	t_list	*list_v1;
	t_list	*list_v2;
	char	*str;
	char	**splited_pipe;
	char	**splited_space;
	char	**splited_in_redirection;
	char	**splited_out_redirection;
}			t_minishell;

void		init_struct(t_minishell *ptr);
void		parsing(t_minishell *ptr);

/* =====  parsing  ===== */

void		build_linked_list_v1(t_minishell *ptr);
int is_there_in_redirection(char *str);
int is_there_out_redirection(char *str);
int			is_there_heredoc(char *str);
int is_there_append(char *str);
void		handle_quotes(t_minishell *ptr);

/*  ===== Error function ===== */

void		ft_perror(char *str, int status);

/*  ===== free function ===== */

void    free_spilte(char    **str);
#endif