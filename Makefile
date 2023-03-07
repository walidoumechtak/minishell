# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:56:35 by woumecht          #+#    #+#              #
#    Updated: 2023/03/07 11:45:41 by hbenfadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address
NAME=minishell

LIBREADLINE=-L .brew/opt/readline/lib
FOLDERREADLINE=-I .brew/opt/readline/include
HEADER		= -I./inc -I./libft/inc
LIBFT		= ./libft/libft.a
CLIB		=  -L./libft -lft 

BUILTINS = ft_echo.c
EXECUTION = ft_exec.c

SRCP= build_linked_list.c is_there_in_redirection.c is_there_out_redirection.c is_there_heredoc.c handle_quotes.c \
	is_there_append.c ft_expaind.c build_list_1.c fill_with.c\

SRCS= parsing.c init_struct.c ft_perror.c free_splite.c build_env.c\

# SRC = $(addprefix ./src/parsing/, $(SRCP)) \
# 	  $(addprefix ./src/, $(SRCS)) \
# 	  main.c \


SRC = $(addprefix ./src/execution/, $(EXECUTION)) \
		$(addprefix ./src/execution/builtins/, $(BUILTINS))
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(HEADER) $(INCB) -c $^ -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(HEADER) $(CLIB) $(OBJ) -lreadline -o $(NAME)
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