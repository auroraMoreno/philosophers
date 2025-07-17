/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:58:40 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/17 09:47:13 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_destroy_mtxs(t_args *philo_args, int forks_created)
{
    int i = 0;
    
    while(i < forks_created)
    {
        pthread_attr_destroy(&philo_args->forks[i]);
        i++;
    }

    if(philo_args->forks)
        free(philo_args->forks);
    
    pthread_mutex_destroy(&philo_args->print_mtx);
    pthread_mutex_destroy(&philo_args->meal_time_mtx);
    pthread_mutex_destroy(&philo_args->sim_end_mtx);
}


void ft_free_philos(t_args *philo_args)
{
    if(philo_args->philos)
    {
        free(philo_args->philos);
        philo_args->philos = NULL;
    }
}