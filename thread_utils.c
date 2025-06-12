/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:44:27 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/12 16:13:43 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *ft_test_routine(void *args) // add el mutex
{
    (void)args;
    //t_args *philo_args = (t_args *)args;
    pthread_mutex_lock(philo->mutex);
    printf("testing\n");
    pthread_mutex_unlock(philo->mutex);
    return (0);
}

void ft_create_threads(t_args *args)
{
    args->philo_ths = malloc(sizeof(pthread_t) * args->num_philo);
    long i = 0;
    while(i < args->num_philo)
    {
        if(pthread_create(&args->philo_ths[i], NULL, &ft_test_routine, args) != 0)
        {
            perror(ERROR_CREATE_TH);
            exit(EXIT_FAILURE); 
        }
        
        // TO-DO: considerar poner pthread join en un bucle a parte 
        if(pthread_join(args->philo_ths[i], NULL) != 0)
        {
            perror(ERROR_JOIN_TH);
        }
        
        args->philos[i].mutex = mutex;
        
        i++;
    }
    
    
  
}

void ft_init_philosophers(t_args *args)
{
    t_philo *philo;
   
    long i = 0;
    philo = malloc(sizeof(t_philo) * args->num_philo);

    if(!philo)
    {
        perror(ERROR_MALLOC);
        exit(EXIT_FAILURE);
    }
    
    while(i < args->num_philo)
    {
        philo->philo_id = i + 1; 
        i++;
    }
    
}

void ft_init_threads(t_args *args, pthread_mutex_t mutex)
{
    printf("creating threads\n");
    ft_init_philosophers(args);
    ft_create_threads(args);
    printf("threads created\n");
}