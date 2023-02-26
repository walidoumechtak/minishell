# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:56:35 by woumecht          #+#    #+#              #
#    Updated: 2023/02/26 15:48:24 by hbenfadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror 
NAME=minishell

LIBREADLINE=-L .brew/opt/readline/lib
FOLDERREADLINE=-I .brew/opt/readline/include
HEADER		= -I./inc -I./libft/inc
LIBFT		= ./libft/libft.a
CLIB		=  -L./libft -lft 


SRC= minishell.c \

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
	make clean -C ./libft
	@echo "Done."
fclean: clean
	@rm -f $(NAME) $(LIBFT)

