/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:50:28 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/23 11:56:02 by aumoreno         ###   ########.fr       */
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


/*philo states*/
#define SLEEP 0
#define EAT 1 
#define THINK 2 

/*philo messages*/
#define TAKEN_FORK "has taken a fork"
#define IS_EATING "is eating"
#define IS_SLEEPING "is sleeping"
#define IS_THINKING "is thinking"
#define PHILO_DIED "died"
#define SIM_ENDED "Ending simulation..."


typedef struct s_philosopher
{
    pthread_t th_philo;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    long philo_id;
    long last_meal_time; 
    int has_to_eat;
    
}t_philo;

typedef struct s_args // cambiar nombre a data 
{
    /*arguments*/
    long num_philo; //numero de filosofos 
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long num_times_to_eat;
    t_philo     *philos; 
    
}t_args;


void ft_init_args(char **argv, t_args *philo_args);
void ft_check_avoid_dying(t_args *args);

/*philo actions*/
void ft_sleep(t_args *data);


/*thread utils*/
void ft_init_data(t_args *args);
void ft_init_philosophers(t_args *args);
void ft_create_threads(t_args *args);
void *ft_test_routine(void *args);

/*time utils*/
long ft_get_time_ms();

/*utils*/
int ft_atoi(char *nbr);
int ft_isdigit(char c);
size_t ft_strlen(char *str);
void ft_print_msg(char *msg, int philo_id);

/*errors*/
void ft_error(char *str);


#endif