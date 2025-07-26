# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 15:50:10 by aumoreno          #+#    #+#              #
#    Updated: 2025/07/25 12:57:50 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = philo

SRCS = main.c init.c monitor.c routine.c philo_actions.c time_utils.c utils.c free.c error.c

CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread  -fno-sanitize=thread 

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