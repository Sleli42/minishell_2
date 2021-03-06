# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/01 19:09:41 by lubaujar          #+#    #+#              #
#    Updated: 2015/09/01 19:09:42 by lubaujar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell2
RM = rm -rf
FLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -I./include/ -I./libft/include/

SRC = main.c \
	init.c \
	list.c \
	env.c \
	commands.c \
	exec_binary.c \
	pipe.c \
	redirection.c \
	builtins_tools.c \
	redirection_tools.c \
	error.c \
	signal.c \
	debug.c

OBJ = $(SRC:.c=.o)
	SRCDIR	= ./srcs/
	OBJDIR	= ./objs/
	INCDIR	= ./include/
	SRCS	= $(addprefix $(SRCDIR), $(SRC))
	OBJS	= $(addprefix $(OBJDIR), $(OBJ))
	INCS	= $(addprefix $(INCDIR), $(INC))

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	@gcc $(FLAGS) -o $@ $^ -L./libft/ -lft
	@echo "\\033[1;34m\tPlease wait ...\\033[0;39m"
	@echo "\\033[1;34m\t\texec ./minishell2\\033[0;39m"

$(OBJS): $(SRCS)
	@make -C libft/
	@gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
	@echo "\\033[1;34mPlease wait ...\\033[0;39m"
	@mkdir -p $(OBJDIR)
	@mv $(OBJ) $(OBJDIR)

clean:
	@echo "\nRM *.o.. \t      \033[35mDELETE!\033[0m"
	@$(RM) $(OBJS)
	@$(RM) *.o

fclean: clean
	@make fclean -C libft/
	@echo "RM ./ft_minishell..   \033[35mDELETE!\033[0m"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re