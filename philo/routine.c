/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:59:45 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 10:24:22 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_simulation(t_args *args)
{
	int	should_end;

	pthread_mutex_lock(&args->sim_end_mtx);
	should_end = args->sim_should_end;
	pthread_mutex_unlock(&args->sim_end_mtx);
	return (should_end);
}

void	ft_only_one_philo(t_philo *philo)
{
	ft_print_msg(TAKEN_FORK, philo, 0);
	ft_my_usleep(philo->args->time_to_die * 2, philo->args);
}

int	ft_run_simulation(t_philo *philo)
{
	ft_take_forks(philo);
	if (ft_check_simulation(philo->args))
	{
		ft_drop_forks(philo);
		return (1);
	}
	ft_eat(philo);
	if (ft_check_simulation(philo->args))
		return (1);
	ft_sleep(philo);
	if (ft_check_simulation(philo->args))
		return (1);
	ft_think(philo);
	return (0);
}

void	*ft_philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->philo_id % 2 == 0)
		ft_my_usleep(philo->args->time_to_eat / 10, philo->args);
	if (philo->args->num_philo == 1)
	{
		ft_only_one_philo(philo);
		return (NULL);
	}
	while (!ft_check_simulation(philo->args))
	{
		if (ft_run_simulation(philo))
			break ;
	}
	return (NULL);
}
