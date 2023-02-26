
#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define NONE "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[91m"
#define GRAY "\033[2;37m"
#define ITALIC "\033[3m"


typedef struct s_mini
{
    char **cmd;
    char *file;
    
}           t_mini;


#endif
