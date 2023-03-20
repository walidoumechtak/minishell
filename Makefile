# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:56:35 by woumecht          #+#    #+#              #
#    Updated: 2023/03/20 15:12:09 by woumecht         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror #-fsanitize=address
NAME=minishell

LIBREADLINE=-L .brew/opt/readline/lib
FOLDERREADLINE=-I .brew/opt/readline/include
HEADER		= -I./inc -I./libft/inc
LIBFT		= ./libft/libft.a
CLIB		=  -L./libft -lft 


# SRC= main.c \
# 	 src/minishell.c \

SRCP= build_linked_list.c is_there_in_redirection.c is_there_out_redirection.c is_there_heredoc.c handle_quotes.c \
	is_there_append.c ft_uncoted_expaind.c ft_coted_expaind.c build_list_1.c fill_with.c build_list_2.c expaind_exit_state.c redirection_syntax.c expaind_heredoc.c\

SRCS= parsing.c init_struct.c ft_perror.c free_splite.c build_env.c ft_putchar_error.c ft_putstr_error.c open_error.c\

SRC = $(addprefix ./src/parsing/, $(SRCP)) \
	  $(addprefix ./src/, $(SRCS)) \
	  main.c \
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) $(HEADER) $(INCB) -c $^ -o $@
	@echo "compiling ..."

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(HEADER) $(CLIB) $(OBJ) -lreadline -o $(NAME)
	
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