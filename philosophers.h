/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:50:28 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/31 12:28:20 by aumoreno         ###   ########.fr       */
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

#ifndef ERROR_NUM_PHILO
#define ERROR_NUM_PHILO "Wrong number of philosophers given.\n"
#endif

#ifndef ERROR_CREATE_TH
#define ERROR_CREATE_TH "Error creating thread.\n"
#endif

#ifndef ERROR_MUTEX_INIT
#define ERROR_MUTEX_INIT "Error initialising mutex.\n"
#endif

#ifndef ERROR_JOIN_TH
#define ERROR_JOIN_TH "Error joining thread.\n"
#endif


/*philo states*/
#define SLEEPING 0
#define EATING 1 
#define THINKING 2 
#define DEAD 3
#define FULL 4

/*philo messages*/
#define TAKEN_FORK "has taken a fork"
#define IS_EATING "is eating"
#define IS_SLEEPING "is sleeping"
#define IS_THINKING "is thinking"
#define PHILO_DIED "died"
#define SIM_ENDED "Ending simulation..."

typedef struct s_philosopher
{
    int philo_id;
    pthread_t th_philo;
    /*fork pointers to the fork mutex array in args, 
        have to be pointer so that we access that array directly
        if they were just values we would be creating a copy of the fork all the time, defeating the purpose of shared forks
    */
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long last_meal_time; 
    int meals_eaten; 
    int has_to_eat;
    int state; //0, 1, 2
    struct s_args *args; 
    
}t_philo;

typedef struct s_args // cambiar nombre a data 
{
    /*arguments*/
    int num_philo; 
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_to_eat;
    long long sim_start_time;
    int sim_should_end; //0 o 1
    pthread_mutex_t *forks; // todos los tenedores que hay 
    pthread_mutex_t meal_time_mtx; // to protect last meal time as it will be accesed by multiple threads: monitor and philospher 
    pthread_mutex_t sim_end_mtx; //to protect the sim should end flag
    pthread_mutex_t print_mtx; 
    t_philo     *philos; 
    
}t_args;





/*init methods*/
void ft_init_args(char **argv, t_args *philo_args);
void ft_init_mtxs(t_args *philo_args);
void ft_init_philos(t_args *philo_args);
void ft_init_threads(pthread_t *monitor, t_args *philo_args);

/*monitoring methods*/
void *ft_monitor_routine(void *philo_args);
int ft_check_philo_death(t_philo *philo);
int ft_check_philos_full(t_args *args);
int ft_single_philo_full(t_philo *philo);

/*routine methods*/
void *ft_philo_routine(void *args);
int ft_check_simulation(t_args *args);
int ft_run_simulation(t_philo *philo);
void ft_only_one_philo(t_philo *philo);

/*philosopher methods*/
void ft_eat(t_philo *philo);
void ft_sleep(t_philo *philo);
void ft_think(t_philo *philo);
void ft_take_forks(t_philo *philo);
void ft_drop_forks(t_philo *philo);


/*time utils*/
long long ft_get_time_ms(void);
void ft_my_usleep(long long time_sleep, t_args *args);

/*free methods*/
void ft_join_philos(t_args *args, int threads_created);
void ft_destroy_mtxs(t_args *philo_args, int forks_created);
void ft_free_philos(t_args *philo_args);

/*utils*/
int ft_atoi(char *nbr);
int ft_isdigit(char c);
size_t ft_strlen(char *str);
void ft_print_msg(char *msg, t_philo *philo, int should_print);


/*errors*/
void ft_error(char *str);


#endif