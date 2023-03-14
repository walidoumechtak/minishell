/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:11:04 by woumecht          #+#    #+#             */
/*   Updated: 2023/03/14 20:38:07 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipe_2(char *str, int *i)
{
    if (str[*i] && str[*i + 1] == '\0')
        return (0);
    while (str[*i])
	{
		if (str[*i] == '\"')
			while (str[++*i] && str[*i] != '\"')
				;
		if (str[*i] == '\'')
			while (str[++*i] && str[*i] != '\'')
				;
		if (str[*i] && str[*i] == '|')
		{
			while (str[++*i] == ' ')
				;
			if (str[*i] == '|')
				return (1);
		}
		(*i)++;
	}
    return (0);
}

int	check_pipe_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (1);
	if (check_pipe_2(str, &i) == 1)
        return (1);
	i = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (1);
	return (0);
}

int check_slach_symbole(char **arr)
{
    int i;
    int j;

    i = 0;
    while (arr[i])
    {
        j = 0;
        while (arr[i][j])
        {
            while (arr[i][j] == ' ')
                j++;
            if (arr[i][j] == '/' && arr[i][j + 1] == ' ')
                return (126);
            else
                break;
        }
        i++;
    }
    return (0);
}

int check_semi_colum(char **arr)
{
    int i;
    int j;

    i = 0;
    while (arr[i] != NULL)
    {
        j = 0;
        while (arr[i][j])
        {
            if (arr[i][j] == '\"')
                while (arr[i][++j] && arr[i][j] != '\"')
                    ;
            if (arr[i][j] == '\'')
                while (arr[i][++j] && arr[i][j] != '\'')
                    ;
            if (arr[i][j] == ';')
                return (1);
            if (arr[i][j] != '\0')
                j++;
        }
        i++;
    }
    return (0);
}

int rederction_syntax_2(char *arr, int *j, int *cpt)
{
    if (arr[*j] == '<')
    {
        while (arr[++(*j)] == ' ')
            ;
        if (arr[*j] == '>' || arr[*j] == '\0' || (arr[*j] == '<' && arr[*j - 1] == ' '))
            return (1);
        while (arr[*j] && arr[(*j)++] == '<')
            (*cpt)++;
        if (*cpt > 2)
            return (1);
    }
    else if (arr[*j] == '>')
    {
        while (arr[++*j] == ' ')
            ;
        if (arr[*j] == '<' || arr[*j] == '\0' || (arr[*j] == '>' && arr[*j - 1] == ' '))
            return (1);
        while (arr[*j] && arr[(*j)++] == '>')
            (*cpt)++;
        if (*cpt > 2)
            return (1);
    }
    return (0);
}

int rederction_syntax(char **arr)
{
    int i;
    int j;
    int cpt;

    i = 0;
    while (arr[i])
    {
        j = 0;
        cpt = 1;
        while (arr[i][j])
        {
            if (arr[i][j] == '\"')
                while (arr[i][++j] && arr[i][j] != '\"')
                        ;
            if (arr[i][j] == '\'')
                while (arr[i][++j] && arr[i][j] != '\'')
                    ;
            if (rederction_syntax_2(arr[i], &j, &cpt) != 0)
                return (1);
            if (arr[i][j] != '\0')
                j++;
        }
        i++;
    }
    return (0);
}


int    parsing(t_minishell *ptr)
{
    int state;
    
    init_struct(ptr);
    if (check_pipe_syntax(ptr->str) == 1)
		return (1);
    if(check_slach_symbole(ptr->splited_pipe) != 0)
        return (126);
    if (check_semi_colum(ptr->splited_pipe) != 0)
        return (1);
    if (rederction_syntax(ptr->splited_pipe) != 0)
        return (1);
    state = build_linked_list(ptr);
    if (state != 0)
        return (state);
    return (0);
}
