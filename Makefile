# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 15:50:10 by aumoreno          #+#    #+#              #
#    Updated: 2025/06/23 10:57:46 by aumoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = philo

SRCS = main.c thread_utils.c philo_actions.c utils.c time_utils.c error.c

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