/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:56:07 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/26 23:42:44 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_single_philo_full(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->meal_time_mtx);
    if(philo->meals_eaten < philo->args->num_times_to_eat)
    {
        pthread_mutex_unlock(&philo->args->meal_time_mtx);
        return (1);
    }
    pthread_mutex_unlock(&philo->args->meal_time_mtx);

    pthread_mutex_lock(&philo->args->sim_end_mtx);
    if(!philo->args->sim_should_end)
        philo->state = FULL;
    pthread_mutex_unlock(&philo->args->sim_end_mtx);
    return (0);
}

int ft_check_philos_full(t_args *args)
{
    int all_full;
    int i;
    if(args->num_times_to_eat == 0)
        return (0);
    
    i = 0;
    all_full = 1;
    while(i < args->num_philo)
    {
        if(ft_single_philo_full(&args->philos[i]))
            all_full = 0;
        
        i++;
    }

    if(all_full)
    {
        pthread_mutex_lock(&args->sim_end_mtx);
        if(!args->sim_should_end)
            args->sim_should_end = 1;
        pthread_mutex_unlock(&args->sim_end_mtx);
        return (1);
    }
    return (0);
    //return (ft_end_if_full(args, all_full));
}

int ft_check_philo_death(t_philo *philo)
{
    long long time_elapse_last_meal; 
    
    pthread_mutex_lock(&philo->args->meal_time_mtx);
    time_elapse_last_meal = ft_get_time_ms() - philo->last_meal_time;
    pthread_mutex_unlock(&philo->args->meal_time_mtx);
    
    if(time_elapse_last_meal > philo->args->time_to_die)
    {
        pthread_mutex_lock(&philo->args->sim_end_mtx); // para que no accedan al if a la vex
        if(!philo->args->sim_should_end)
        {
            philo->args->sim_should_end = 1;
            pthread_mutex_unlock(&philo->args->sim_end_mtx);
            ft_print_msg(PHILO_DIED, philo->philo_id);
            philo->state = DEAD;
            return (1);
        }
        pthread_mutex_unlock(&philo->args->sim_end_mtx);
        return (1);
    }
    return (0);
}

void *ft_monitor_routine(void *philo_args)
{
    int i;
    t_args *args = (t_args *)philo_args;
    // ejecutar constantemente bucle monitor
    while(1)
    {
        //por cada filosofo checkamos si:
        //full o death
        i = 0;
        while(i < args->num_philo)
        {
            if(ft_check_philo_death(&args->philos[i]) || ft_check_philos_full(args))
                return (NULL);
            i++;
        }    
        // hacer un sleep
        usleep(1000); // le damos un break al cpu 
        //checkamos si sim over;
        if(ft_check_simulation(args))
            return (NULL); // review this  
    }
}