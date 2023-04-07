/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:48:56 by woumecht          #+#    #+#             */
/*   Updated: 2023/04/07 13:44:30 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_support(t_minishell *ptr)
{
	int	state;

	if (g_state_sigint == 1)
	{
		g_state_sigint = 0;
		ptr->exit_state = 1;
	}
	init_struct(ptr);
	state = parsing(ptr);
	if (state != 0)
	{
		all_errors_parsing(ptr, state);
		free(ptr->str);
		free_spilte(ptr->splited_pipe);
		return (1);
	}
	shift_array_of_nullter(ptr);
	ft_exec(ptr);
	end_of_program(ptr);
	return (0);
}

void	ptr_failed(t_minishell *ptr)
{
	g_state_sigint = 0;
	if (!ptr)
	{
		ft_putstr_fd("Error: memory allocation\n", 2);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*ptr;

	(void)av;
	(void)ac;
	ptr = malloc(sizeof(t_minishell));
	ptr_failed(ptr);
	ptr->env = build_env_list(env);
	ptr->exit_state = 0;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, signal_handler1);
		ptr->str = readline(RED "Minishell" NONE GREEN "-$ " NONE);
		if (ptr->str == NULL || ptr->str[0] == '\0')
		{
			if (ptr->str == NULL)
				exit (ptr->exit_state);
			free(ptr->str);
			continue ;
		}
		add_history(ptr->str);
		if (main_support(ptr) != 0)
			continue ;
	}
	free(ptr);
}
