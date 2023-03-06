#include "minishell.h"

void    free_spilte(char    **str)
{
    int i;

    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}