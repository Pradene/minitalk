# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpradene <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 00:33:43 by lpradene          #+#    #+#              #
#    Updated: 2023/01/31 00:33:45 by lpradene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_C	= srcs/client.c
SRCS_S	= srcs/server.c
UTILS	= srcs/strlen.c \
			srcs/itoa.c

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

SERVER	= server
CLIENT	= client

OBJS_C = $(SRCS_C:.c=.o)
OBJS_S = $(SRCS_S:.c=.o)
OBJS_U = $(UTILS:.c=.o)

all: server client

$(NAME): all

server: $(OBJS_S) $(OBJS_U)
	$(CC) $(OBJS_S) $(OBJS_U) -o $(SERVER)

client: $(OBJS_C) $(OBJS_U)
	$(CC) $(OBJS_C) $(OBJS_U) -o $(CLIENT)

clean:
	rm -f $(OBJS_S) $(OBJS_C) $(OBJS_U)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: re fclean clean all
