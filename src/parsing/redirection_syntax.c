#include "minishell.h"

int rederction_syntax(char *arr)
{
    char **split;
    int k;
    int j;
    int cpt;

    j = 0;
    split = ft_split(arr, ' ');
    while (split[j])
    {
        if (ft_strncmp(split[j], ">", ft_strlen(split[j])) == 0 || ft_strncmp(split[j], "<", ft_strlen(split[j])) == 0
        || ft_strncmp(split[j], ">>", ft_strlen(split[j])) == 0 || ft_strncmp(split[j], "<<", ft_strlen(split[j])) == 0)
        {
            if (split[j + 1] == NULL)
            {
                free_spilte(split);
                return (1);
            }
        }
        else if (split[j + 1] && ((ft_strncmp(split[j], ">", 1) == 0 || ft_strncmp(split[j], "<", 1) == 0) 
        && (ft_strncmp(split[j + 1], ">", 1) == 0 || ft_strncmp(split[j + 1], "<", 1) == 0)))
        {
            free_spilte(split);
            return (1);
        }
        else
        {
            k = 0;
            cpt = 0;
            if (ft_strncmp(split[j], ">", 1) == 0)
            {
                while (split[j][k] == '>')
                {
                    cpt++;
                    k++;
                }
            }
            else if (ft_strncmp(split[j], "<", 1) == 0)
            {
                while (split[j][k] == '<')
                {
                    cpt++;
                    k++;
                }
            }
            if (cpt > 2)
            {
                free_spilte(split);
                return (1);
            }
        }
        j++;
    }
    free_spilte(split);
    return (0);
}