# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 15:56:25 by hbenfadd          #+#    #+#              #
#    Updated: 2023/03/25 15:32:08 by hbenfadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= minishell
LIBREADLINE		= -L /goinfre/hbenfadd/homebrew/Cellar/readline/8.2.1/lib -lreadline
INCREADLINE		= -I /goinfre/hbenfadd/homebrew/Cellar/readline/8.2.1/include
HEADER			= -I./inc -I./libft/inc 
CFLAGS			= -Wall -Wextra -Werror -fsanitize=address
LIBFT			= ./libft/libft.a
CLIB			=  -L./libft -lft 

BUILTINS		= ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pipe.c ft_unset.c
EXECUTILITIES	= ft_exec.c exec_is_builtins.c convert_list_env.c check_cmd.c add_to_env.c ft_puterror.c

SRCP= build_linked_list.c is_there_in_redirection.c is_there_out_redirection.c is_there_heredoc.c handle_quotes.c \
	is_there_append.c ft_uncoted_expaind.c ft_coted_expaind.c build_list_1.c fill_with.c build_list_2.c \
	 expaind_exit_state.c redirection_syntax.c expaind_heredoc.c free_linked_lists.c syntax.c open_out_file.c\

PARSING= parsing.c init_struct.c ft_perror.c free_splite.c build_env.c open_error.c free_env.c\

SRC = $(addprefix ./src/parsing/, $(SRCP)) \
	  $(addprefix ./src/, $(PARSING)) \
	  $(addprefix ./src/builtins/utilities/, $(EXECUTILITIES)) \
	  $(addprefix ./src/builtins/, $(BUILTINS)) \
 	  main.c 
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) $(HEADER) $(INCB) -c $^ -o $@
	@echo "compiling ..."

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(HEADER) $(INCREADLINE) $(OBJ) $(CLIB) $(LIBREADLINE) -o $(NAME)
	#$(CC) $(CFLAGS) $(HEADER)  $(OBJ) $(CLIB) -o $(NAME) 

$(LIBFT):
	@echo "$(YALLOW)\n[libft]:$(NONE)"
	@make all -C ./libft
clean:
	@echo "cleaninig..."
	@sleep 0.5
	@rm -f $(OBJ)
	@make clean -C ./libft
	@echo "Done."
fclean: clean
	@rm -f $(NAME) $(LIBFT)

re:fclean all