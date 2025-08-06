/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:56:07 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 09:44:32 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_single_philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->meal_time_mtx);
	if (philo->meals_eaten < philo->args->num_times_to_eat)
	{
		pthread_mutex_unlock(&philo->args->meal_time_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->meal_time_mtx);
	pthread_mutex_lock(&philo->args->sim_end_mtx);
	if (!philo->args->sim_should_end)
		philo->state = FULL;
	pthread_mutex_unlock(&philo->args->sim_end_mtx);
	return (0);
}

int	ft_check_philos_full(t_args *args)
{
	int	all_full;
	int	i;

	if (args->num_times_to_eat == 0)
		return (0);
	i = 0;
	all_full = 1;
	while (i < args->num_philo)
	{
		if (ft_single_philo_full(&args->philos[i]))
			all_full = 0;
		i++;
	}
	if (all_full)
	{
		pthread_mutex_lock(&args->sim_end_mtx);
		if (!args->sim_should_end)
			args->sim_should_end = 1;
		pthread_mutex_unlock(&args->sim_end_mtx);
		return (1);
	}
	return (0);
}

int	ft_check_philo_death(t_philo *philo)
{
	long long	time_elapse_last_meal;

	pthread_mutex_lock(&philo->args->meal_time_mtx);
	time_elapse_last_meal = ft_get_time_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->args->meal_time_mtx);
	if (time_elapse_last_meal > philo->args->time_to_die)
	{
		pthread_mutex_lock(&philo->args->sim_end_mtx);
		if (!philo->args->sim_should_end)
		{
			philo->args->sim_should_end = 1;
			pthread_mutex_unlock(&philo->args->sim_end_mtx);
			ft_print_msg(PHILO_DIED, philo, 1);
			philo->state = DEAD;
			return (1);
		}
		pthread_mutex_unlock(&philo->args->sim_end_mtx);
		return (1);
	}
	return (0);
}

void	*ft_monitor_routine(void *philo_args)
{
	int		i;
	t_args	*args;

	args = (t_args *)philo_args;
	while (1)
	{
		i = 0;
		while (i < args->num_philo)
		{
			if (ft_check_philo_death(&args->philos[i])
				|| ft_check_philos_full(args))
				return (NULL);
			i++;
		}
		usleep(1000);
		if (ft_check_simulation(args))
			return (NULL);
	}
}
