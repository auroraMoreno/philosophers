/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:05:45 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/17 09:48:01 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long ft_get_time_ms(void)
{
    struct timeval curr_time;
    long long ms; 
    gettimeofday(&curr_time, NULL);
    ms = (curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000);
    return ms;
}