
#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "get_next_line.h"
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

typedef struct s_node
{
	char			**cmd;
	int				i_pipe;
}					t_node;


typedef struct s_mini
{
	char			*str;
	char			**splited_pipe;
	char			**splited_redirection;
}					t_minishell;
#endif