/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:05:45 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 10:19:54 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_my_usleep(long long time_sleep, t_args *args)
{
	long long	start;

	start = ft_get_time_ms();
	while ((ft_get_time_ms() - start) < time_sleep
		&& !ft_check_simulation(args))
		usleep(50);
}

long long	ft_get_time_ms(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}
