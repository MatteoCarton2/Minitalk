# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 19:19:52 by mcarton           #+#    #+#              #
#    Updated: 2025/03/24 20:08:44 by mcarton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Noms des programmes
SERVER = server
CLIENT = client

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Sources
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Objets
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

# ft_printf
PRINTF_DIR = ./ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
INCLUDES += -I$(PRINTF_DIR)

# Règles
all: $(SERVER) $(CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF): $(LIBFT)
	make -C $(PRINTF_DIR) LIBFT_PATH=$(LIBFT_DIR)

$(SERVER): $(PRINTF) $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -L$(PRINTF_DIR) -lftprintf -o $(SERVER)

$(CLIENT): $(PRINTF) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -L$(PRINTF_DIR) -lftprintf -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re