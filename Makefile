# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 15:50:10 by aumoreno          #+#    #+#              #
#    Updated: 2025/08/06 08:02:46 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = philo

SRCS = main.c init.c monitor.c routine.c philo_actions.c time_utils.c utils.c free.c error.c

CC = gcc 
CFLAGS = -Wall -Wextra -Werror -pthread

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