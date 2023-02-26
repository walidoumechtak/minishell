# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:56:35 by woumecht          #+#    #+#              #
#    Updated: 2023/02/26 15:56:37 by woumecht         ###   ########.fr        #
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


SRC= main.c \
	 src/minishell.c \
	 
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

