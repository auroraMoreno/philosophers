/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:47:49 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/26 23:37:21 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    
    t_args philo_args;
    pthread_t monitor;
    
    //checks args
    // minimo 4 args
    // si es 3 o 6, error
    if(argc < 5 || argc > 6)
        ft_error(ERROR_ARGS);
        
    //init data
        //init args
    ft_init_args(argv, &philo_args); // add check 
        //init mutex
    ft_init_mtxs(&philo_args);
        //init philo
    ft_init_philos(&philo_args);
    
    //init threads
    ft_init_threads(&monitor, &philo_args);

    //thread join
    pthread_join(monitor, NULL);

    // free memory 
    ft_join_philos(&philo_args, philo_args.num_philo);
    ft_destroy_mtxs(&philo_args, philo_args.num_philo);
    ft_free_philos(&philo_args);

    return (0);
}