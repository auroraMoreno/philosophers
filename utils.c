/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:23:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 10:28:37 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_msg(char *msg, t_philo *philo, int should_print)
{
	long long	ts;

	pthread_mutex_lock(&philo->args->sim_end_mtx);
	if (philo->args->sim_should_end && !should_print)
	{
		pthread_mutex_unlock(&philo->args->sim_end_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->args->sim_end_mtx);
	ts = ft_get_time_ms() - philo->args->sim_start_time;
	pthread_mutex_lock(&philo->args->print_mtx);
	if (!ft_check_simulation(philo->args) || should_print)
		printf("%lld %d %s \n", ts, philo->philo_id, msg);
	pthread_mutex_unlock(&philo->args->print_mtx);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	long	res;

	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			ft_error(ERROR_NOT_NUMBER);
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}
