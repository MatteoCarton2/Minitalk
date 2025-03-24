# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 20:17:36 by mcarton           #+#    #+#              #
#    Updated: 2025/03/24 20:21:24 by mcarton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: server.o libs
	$(CC) -o $@ $< -Llibft -lft -Lft_printf -lftprintf

client: client.o libs
	$(CC) -o $@ $< -Llibft -lft -Lft_printf -lftprintf

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libs: libft ft_printf

libft:
	make -C libft

ft_printf:
	make -C ft_printf

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	make -C ft_printf clean
	
fclean: clean
	rm -f server client
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: all bonus libft ft_printf libs clean fclean re