# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenfadd <hbenfadd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:56:35 by woumecht          #+#    #+#              #
#    Updated: 2023/03/17 15:53:24 by hbenfadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=cc
CFLAGS			=-Wall -Wextra -Werror -fsanitize=address
NAME			=minishell
LIBREADLINE		=-L /Users/hbenfadd/goinfre/homebrew/opt/readline/lib -lreadline
INCREADLINE		=-I /Users/hbenfadd/goinfre/homebrew/opt/readline/include
HEADER			= -I./inc -I./libft/inc 
LIBFT			= ./libft/libft.a
CLIB			=  -L./libft -lft 

BUILTINS = ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pipe.c ft_unset.c
EXECUTION = ft_exec.c exec_is_builtins.c

SRC = $(addprefix ./src/execution/, $(EXECUTION)) \
		$(addprefix ./src/execution/builtins/, $(BUILTINS))\
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(HEADER) $(INCB) -c $^ -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(HEADER) $(INCREADLINE) $(CLIB) $(LIBREADLINE) $(OBJ)  -o $(NAME)
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