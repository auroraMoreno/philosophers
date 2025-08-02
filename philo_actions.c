/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:26:33 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/31 12:26:49 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// eat: fork logic, mutex 

void ft_take_forks(t_philo *philo)
{
    //check if odd / even
    //depende si odd o even empezamos lockeando uno u otro fork 
    if(philo->philo_id % 2 == 0) // even
    {
        pthread_mutex_lock(philo->left_fork);
        ft_print_msg(TAKEN_FORK, philo, 0);
        pthread_mutex_lock(philo->right_fork);
        ft_print_msg(TAKEN_FORK, philo, 0);
    }
    else //odd
    {
        pthread_mutex_lock(philo->right_fork);
        ft_print_msg(TAKEN_FORK,philo, 0);
        pthread_mutex_lock(philo->left_fork);
        ft_print_msg(TAKEN_FORK, philo, 0);
    }
}

void ft_drop_forks(t_philo *philo)
{
    if(philo->right_fork)
        pthread_mutex_unlock(philo->right_fork);
    //then left
    pthread_mutex_unlock(philo->left_fork);
}

//update last meal time
//update state 
void ft_eat(t_philo *philo)
{
    if(ft_check_simulation(philo->args))
        return; //REVIEW 
    
    philo->state =  EATING;
    ft_print_msg(IS_EATING, philo, 0);
    
    pthread_mutex_lock(&philo->args->meal_time_mtx);
    philo->last_meal_time = ft_get_time_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->args->meal_time_mtx);

    //give time to eat:
    ft_my_usleep(philo->args->time_to_eat, philo->args);
    //drop forks
    ft_drop_forks(philo);
    //state
    philo->state = SLEEPING;
    
}

// sleep 
void ft_sleep(t_philo *philo)
{
    if(ft_check_simulation(philo->args))
        return; // REVIEW THIS
    // el estado del philo está sleeping porq despues de comer duerme
    ft_print_msg(IS_SLEEPING, philo, 0);
    ft_my_usleep(philo->args->time_to_sleep, philo->args);
}


// think
void ft_think(t_philo *philo)
{
    long long thinking_time; 
    long long meal_time_passed; 
    //check if sim isnt over
    if(ft_check_simulation(philo->args))
        return;
    //message and state
    ft_print_msg(IS_THINKING, philo, 0);
    //check si mas de 1 philo y si mas comer q dormir
    if(philo->args->num_philo > 1 && 
    philo->args->time_to_eat > philo->args->time_to_sleep)
    {
        //calcular tiempo de pensar
        thinking_time = (philo->args->time_to_eat - philo->args->time_to_sleep) / 2;
        // si 0 o menor => 1
        if(thinking_time <= 0)
            thinking_time = 1;
        //mutex y last meal time
        pthread_mutex_lock(&philo->args->meal_time_mtx);
        meal_time_passed = ft_get_time_ms() - philo->last_meal_time;
        pthread_mutex_unlock(&philo->args->meal_time_mtx);
        // SOLO PIENSA SI NO SE MUERE POR "ESPERA PAR COMER"
        //sleep => think time
        if(meal_time_passed + thinking_time < philo->args->time_to_die)
            ft_my_usleep(thinking_time, philo->args);
    }

        
}