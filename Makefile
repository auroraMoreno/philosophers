# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 15:50:10 by aumoreno          #+#    #+#              #
#    Updated: 2025/05/24 10:50:32 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = philo

SRCS = main.c utils.c error.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

OBJS = ${SRCS:.c=.o}

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) ${SRCS} -o $(EXEC)

all: $(EXEC)

clean:
	@$(RM) $(OBJS)

fclean:  clean
	@$(RM) $(EXEC)
	@$(RM) $(OBJS)
	
re: fclean all

.PHONY: all clean fclean re