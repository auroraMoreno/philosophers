/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:05:45 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/09 11:07:09 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long ft_get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long s = tv.tv_sec;
    long ms = s * 1000;
    return ms;
}