# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:56:35 by woumecht          #+#    #+#              #
#    Updated: 2023/02/26 13:39:30 by woumecht         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror 
NAME=minishell

LIBREADLINE=-L .brew/opt/readline/lib
FOLDERREADLINE=-I .brew/opt/readline/include

SRC= main.c \
	 src/minishell.c \
	 libft/ft_split.c \
	 libft/ft_strjoin.c \
	 libft/ft_strlen.c \
	 libft/ft_strdup.c \
	 libft/ft_lstnew.c \
	 libft/ft_lstadd_back.c \
	 libft/ft_lstadd_front.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	@echo "cleaninig..."
	@sleep 0.5
	@rm -f $(OBJ)
	@echo "Done."
fclean: clean
	@rm -f $(NAME)

