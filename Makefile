# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 12:16:27 by cgeoffra          #+#    #+#              #
#    Updated: 2023/11/06 15:26:17 by cgeoffra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror -g
THREAD = -lpthread

SRCS_FOLDER = src/
SRCS = main.c check.c init.c thread.c free.c utils.c
OBJS_MENDA = $(addprefix $(SRCS_FOLDER), $(SRCS:%.c=%.o))

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS_MENDA)
	@gcc $(FLAGS) $(OBJS_MENDA) $(THREAD) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJS_MENDA)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re
