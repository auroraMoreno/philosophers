/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:58:40 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 09:04:13 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_join_philos(t_args *args, int threads_created)
{
	int	i;

	i = 0;
	while (i < threads_created)
	{
		pthread_join(args->philos[i].th_philo, NULL);
		i++;
	}
}

void	ft_destroy_mtxs(t_args *philo_args, int forks_created)
{
	int	i;

	i = 0;
	while (i < forks_created)
	{
		pthread_mutex_destroy(&philo_args->forks[i]);
		i++;
	}
	if (philo_args->forks)
		free(philo_args->forks);
	pthread_mutex_destroy(&philo_args->print_mtx);
	pthread_mutex_destroy(&philo_args->meal_time_mtx);
	pthread_mutex_destroy(&philo_args->sim_end_mtx);
}

void	ft_free_philos(t_args *philo_args)
{
	if (philo_args->philos)
	{
		free(philo_args->philos);
		philo_args->philos = NULL;
	}
}
