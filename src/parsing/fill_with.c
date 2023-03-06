#include "minishell.h"

void    fill_with(char *str,char old, char c)
{
    int i;

    if (!str)
        return ;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\"')
        {
            i++;
            while (str[i] != '\"')
            {
                if (str[i] == old)
                    str[i] = c;
                i++;
            }
            // i++;
        }
        else if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'')
            {
                if (str[i] == old)
                    str[i] = c;
                i++;
            }
            // i++;
        }
        i++;
    }

}