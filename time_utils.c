/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:05:45 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/26 23:59:16 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_my_usleep(long long time_sleep, t_args *args)
{
    long long start_time;
    long long time_passed; //elapsed
    long long time_left; //remaining
    long long time_sleep_micro; //for more precission

    start_time = ft_get_time_ms();
    time_sleep_micro = time_sleep * 1000;  
    time_left = time_sleep_micro;
    while(time_left > 0 && ft_check_simulation(args))
    {
        time_passed = (ft_get_time_ms() - start_time) * 1000;
        time_left = time_sleep_micro - time_passed;
        if(time_left > 100000)
            usleep(time_left / 2);
        else if(time_left > 0)
            usleep(time_left);
    }
    
}

long long ft_get_time_ms(void)
{
    struct timeval curr_time;
    long long ms; 
    gettimeofday(&curr_time, NULL);
    ms = (curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000);
    return ms;
}