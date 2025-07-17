/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:44:27 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/24 12:27:39 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *ft_test_routine(void *args) // add el mutex
{
    int i = 0;
    t_args *philo_args = (t_args *)args;
    t_philo *philos = philo_args->philos;
    
    //si num of philo es odd they sleep at the begining  
    if(philo_args->num_philo % 2 != 0)
    {
        while(i < philo_args->num_philo)
        {   
            printf("%ld\n", philo_args->philos[i].philo_id);
            ft_sleep(philo_args->time_to_eat / 2);
            ft_print_msg(IS_SLEEPING, philo_args->philos[i].philo_id);
            i++;
        }
    }

    //hacer funcion ft_take_fork()
    printf("testing\n");
    return (0);
}

void ft_create_threads(t_args *args)
{
    args->philos = malloc(sizeof(t_philo) * args->num_philo);
    long i = 0;
    while(i < args->num_philo)
    {
        //printf("%ld\n", args->philos[i].philo_id);
        if(pthread_create(&args->philos[i].th_philo, NULL, &ft_test_routine, &args->philos[i]) != 0)
        {
            perror(ERROR_CREATE_TH);
            exit(EXIT_FAILURE);
        }    
        i++;
    }

    i = 0;
    while(i < args->num_philo)
    {
        // // TO-DO: considerar poner pthread join en un bucle a parte 
        if(pthread_join(args->philos[i].th_philo, NULL) != 0)
            perror(ERROR_JOIN_TH);
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
        philo[i].philo_id = i + 1; 

        philo[i].last_meal_time = 0; 
        i++;
    }

    args->philos = philo;    
}

void ft_init_data(t_args *args)
{
    printf("creating threads\n");
    ft_init_philosophers(args);
    ft_create_threads(args);
    printf("threads created\n");
}