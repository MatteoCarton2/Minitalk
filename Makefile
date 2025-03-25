# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 10:45:40 by mcarton           #+#    #+#              #
#    Updated: 2025/03/25 10:45:41 by mcarton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME_S = server
NAME_C = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_S = server.c
SRC_C = client.c

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

LIBFT = libft/libft.a

all: $(NAME_S) $(NAME_C)

bonus: all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME_S): $(OBJ_S) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_S) -o $@ -L libft -lft

$(NAME_C): $(OBJ_C) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_C) -o $@ -L libft -lft

clean:
	rm -f $(OBJ_S) $(OBJ_C)
	make -C libft clean

fclean: clean
	rm -f $(NAME_S) $(NAME_C)
	make -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
