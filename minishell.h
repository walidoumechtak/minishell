/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:49:11 by woumecht          #+#    #+#             */
/*   Updated: 2023/02/26 13:45:46 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_list
{
	char			**cmd;
	struct s_node	*next;
	int				index_pipe;
}					t_list;

typedef struct s_mini
{
	char			*str;
	char			**splited_pipe;
	char			**splited_redirection;
}					t_minishell;

/* ======== libft ======= */

void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst);
t_list				*ft_lstnew(int index_pipe);
int					ft_lstsize(t_list *lst);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);

#endif