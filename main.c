/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:47:49 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/12 16:13:29 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
}


int main(int argc, char **argv)
{
    // minimo 4 args
    // si es 3 o 6, error

    t_args *philo_args;
    pthread_mutex_t mutex;
    
    if(argc < 5 || argc > 6)
        ft_error(ERROR_ARGS);
    
    
    philo_args = (t_args *)malloc(sizeof(t_args));
    if(!philo_args)
        ft_error(ERROR_MALLOC);
    
    
    ft_init_args(argv, philo_args);
    
    // try print here a philo args
   // printf("Number philo: %ld \n", philo_args->num_philo);
    // vamos a crear una structura philo con pthread y con el id_philosopher (que sea based on number que sea, ver subject X )
    // vamos a hacer una lista de philos y ahi vamos a ir guardando los threads 
    pthread_mutex_init(&mutex, NULL); //UN MUTEX POR CADA PHILO
    ft_init_threads(philo_args, mutext);
    //hacer método init threads
    //probar una simple rutina
    
    // DELETE THE FOLLOWING WHEN NO LONGER NEEDED 

    pthread_mutex_destroy(&mutex);
    return (0);

}