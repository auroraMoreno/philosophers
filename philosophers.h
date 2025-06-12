/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:50:28 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/12 16:12:57 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>

#ifndef ERROR_ARGS
#define ERROR_ARGS "Wrong arguments given.\n"
#endif

#ifndef ERROR_MALLOC
#define ERROR_MALLOC "Error allocating memory.\n"
#endif

#ifndef ERROR_NOT_NUMBER
#define ERROR_NOT_NUMBER "Argument(s) not a valid number.\n"
#endif

#ifndef ERROR_CREATE_TH
#define ERROR_CREATE_TH "Error creating thread.\n"
#endif


#ifndef ERROR_JOIN_TH
#define ERROR_JOIN_TH "Error joining thread.\n"
#endif

typedef struct s_philosopher
{
    //add mutex here ? 
    pthread_mutex_t *mutex;
    long philo_id;
    // TO-DO: add last_meal_time 
    
}t_philo;

typedef struct s_args
{
    /*arguments*/
    long num_philo; //numero de filosofos 
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long num_times_to_eat;
    pthread_t *philo_ths;
    t_philo     *philos; 
    
}t_args;




void ft_init_args(char **argv, t_args *philo_args);

/*thread utils*/
void ft_init_threads(t_args *args);
void ft_init_philosophers(t_args *args);
void ft_create_threads(t_args *args);
void *ft_test_routine(void *args);

/*time utils*/
long ft_get_time_ms();

/*utils*/
int ft_atoi(char *nbr);
int ft_isdigit(char c);
size_t ft_strlen(char *str);

/*errors*/
void ft_error(char *str);


#endif