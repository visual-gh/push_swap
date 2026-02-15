# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Visual <github.com/visual-gh>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/02 18:09:10 by Visual            #+#    #+#              #
#    Updated: 2026/02/15 14:12:17 by Visual           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

LIBFT	= libft/libft.a
INC		= -Iincludes -Ilibft

SRCS	= src/main.c \
		  src/stack.c \
		  src/parsing/parse.c \
		  src/parsing/validate.c \
		  src/operations/push.c \
		  src/operations/swap.c \
		  src/operations/rotate.c \
		  src/operations/rev_rotate.c \
		  src/algorithms/radix.c \
		  src/algorithms/small.c

OBJS	= $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft bonus

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
