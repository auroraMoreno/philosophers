/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:59:45 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/21 14:02:09 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_check_simulation(t_args *args)
{
    int should_end;

    pthread_mutex_lock(&args->sim_end_mtx);
    should_end = args->sim_should_end;
    pthread_mutex_unlock(&args->sim_end_mtx);
    return(should_end);
}

// wait until they die
// CHECK THIS 
void ft_only_one_philo(t_philo *philo)
{
    ft_print_msg(TAKEN_FORK, philo->philo_id);
    ft_my_usleep(philo->args->time_to_die * 2, philo->args);
}

//STATIC ????
void ft_run_simulation(t_philo *philo)
{
    ft_take_forks(philo);
    if(ft_check_simulation(philo->args))
    {
        ft_drop_forks(philo);
        return; //REVIEW    
    } 
    ft_eat(philo);
    if(ft_check_simulation(philo->args))
        return; //REVIEW    
    ft_sleep(philo);
    if(ft_check_simulation(philo->args))
        return; //REVIEW    
    ft_think(philo);
}

// return value ?
void ft_philo_routine(t_philo *philo)
{
    // check if philo odd 
    if(philo->philo_id % 2 == 0)
         //set sleep & desynchronize actions to prevent deadlocks & data races
        ft_my_usleep(philo->args->time_to_eat / 10, philo->args);
   
    // handle single philosopher case
    if(philo->args->num_philo == 1)
        ft_only_one_philo(philo);
    //run simulation
    while(!ft_check_simulation(philo->args))
    {
        // checks ???
        ft_run_simulation(philo);
    }
        //while running => perform actions
}