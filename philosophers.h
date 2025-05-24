/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:50:28 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/24 11:18:05 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifndef ERROR_ARGS
#define ERROR_ARGS "Wrong arguments given.\n"
#endif

#ifndef ERROR_MALLOC
#define ERROR_MALLOC "Error allocating memory.\n"
#endif

#ifndef ERROR_NOT_NUMBER
#define ERROR_NOT_NUMBER "Argument(s) not a valid number.\n"
#endif


typedef struct s_args
{
    long num_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long num_times_to_eat;
    
}t_args;




void ft_init_args(char **argv, t_args *philo_args);

/*utils*/
int ft_atoi(char *nbr);
int ft_isdigit(char c);
size_t ft_strlen(char *str);

/*errors*/
void ft_error(char *str);


#endif