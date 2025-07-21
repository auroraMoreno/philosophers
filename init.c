/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:37:02 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/18 12:58:30 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void ft_init_threads(pthread_t *monitor, t_args *philo_args)
{
    int i;
    //init philo threads;
    philo_args->sim_start_time = ft_get_time_ms();
    i = 0;
    while(i < philo_args->num_philo)
    {
        if(pthread_create(&philo_args->philos[i].th_philo, NULL, ft_philo_routine, &philo_args->philos[i]) != 0)
        {
            // put this in a single functions ? 
            ft_free_philos(philo_args);
            ft_destroy_mtxs(&philo_args, philo_args->num_philo);
            ft_error(ERROR_CREATE_TH);
        }
        i++;
    }
    //init monitor;
    if(pthread_create(monitor, NULL, monitor_routine, philo_args) != 0)
    {
        pthread_mutex_lock(&philo_args->sim_end_mtx);
        philo_args->sim_should_end = 1;
        pthread_mutex_unlock(&philo_args->meal_time_mtx);
        ft_free_philos(philo_args);
        ft_destroy_mtxs(&philo_args, philo_args->num_philo);
        ft_error(ERROR_CREATE_TH);
    }
}

//considerar que devuelva un int para checkear los errores

void ft_init_philos(t_args *philo_args)
{
    int i;
    philo_args->philos = malloc(sizeof(t_philo) * philo_args->num_philo);
    if(!philo_args->philos)
    {
        ft_destroy_mtxs(&philo_args, philo_args->num_philo);
        ft_error(ERROR_MALLOC);
    }

    i = 0;
    while(i < philo_args->num_philo)
    {
        // consider init_philo_node method
        philo_args->philos[i].philo_id = i + 1;
        philo_args->philos[i].last_meal_time = 0;
        philo_args->philos[i].meals_eaten = 0;
        philo_args->philos[i].has_to_eat = 0;
        philo_args->philos[i].state = THINKING;
        philo_args->philos[i].th_philo = NULL;
        // tenedor derecho e izquierdo en terminos de indice de array
        philo_args->philos[i].left_fork = &philo_args->forks[i];
        //if only 1 philo:
        if(philo_args->num_philo == 1)
            philo_args->philos[i].right_fork = NULL;
        else
            philo_args->philos[i].right_fork = &philo_args->forks[(i + 1) % philo_args->num_philo];
        philo_args->philos[i].args = philo_args;
        i++;   
    }
}


void ft_init_mtxs(t_args *philo_args)
{
    // init fork mutex
    int i;
    philo_args->forks = malloc(sizeof(pthread_mutex_t) * philo_args->num_philo);
    if(!philo_args->forks)
        ft_error(ERROR_MALLOC);
    i = 0;
    while(i < philo_args->num_philo)
    {
        if(pthread_mutex_init(&philo_args->forks[i], NULL) != 0)
        {
            ft_destroy_mtxs(&philo_args, i);
            ft_error(ERROR_MUTEX_INIT);
        } // Null ?? 
            //check if unlocked ?? 
        i++;
    }
    // init other mutex
        // init print mutex
    if(pthread_mutex_init(&philo_args->print_mtx, NULL) != 0)
    {
        ft_destroy_mtxs(&philo_args, philo_args->num_philo); 
        ft_error(ERROR_MUTEX_INIT);
    }  
        // init meal time mutex
    if(pthread_mutex_init(&philo_args->meal_time_mtx, NULL) != 0)
    {
        ft_destroy_mtxs(&philo_args, philo_args->num_philo); 
        ft_error(ERROR_MUTEX_INIT);
    }
        // init end sim mutex
    if(pthread_mutex_init(&philo_args->sim_end_mtx, NULL) != 0)
    {
        ft_destroy_mtxs(&philo_args, philo_args->num_philo); 
        ft_error(ERROR_MUTEX_INIT);
    }
}


void ft_init_args(char **argv, t_args *philo_args)
{
    philo_args->num_philo = ft_atoi(argv[1]);
    philo_args->time_to_die = ft_atoi(argv[2]);
    philo_args->time_to_eat = ft_atoi(argv[3]);
    philo_args->time_to_sleep = ft_atoi(argv[4]);
    if(!argv[5])
        philo_args->num_times_to_eat = 0;
    else 
        philo_args->num_times_to_eat = ft_atoi(argv[5]);
    philo_args->sim_start_time = 0;
    philo_args->sim_should_end = 0;
    philo_args->forks = NULL;
    philo_args->philos = NULL;

    if((philo_args->num_philo <= 0 || philo_args->num_philo > 200) || 
        philo_args->time_to_die <= 0 
        || philo_args->time_to_eat <= 0
        || philo_args->time_to_sleep <= 0 ||
    argv[5] && philo_args->num_times_to_eat <= 0) //review esto considerar usar argc
        ft_error(ERROR_NUM_PHILO);

    //init mutex to null? 
}



