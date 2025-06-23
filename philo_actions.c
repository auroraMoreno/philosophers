/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:26:33 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/23 12:25:16 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// eat: fork logic, mutex 

void ft_eat()
{
    
}

// sleep 
void ft_sleep(int time_to_sleep)
{
    if(usleep(time_to_sleep) < -1)
        ft_error("Error in sleep.");
}


// think
void ft_think()
{
    
}