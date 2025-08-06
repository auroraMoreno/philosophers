/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:56:35 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 10:27:43 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_mutex_error(t_args *philo_args)
{
	ft_destroy_mtxs(philo_args, philo_args->num_philo);
	ft_error(ERROR_MUTEX_INIT);
}

void	ft_error_monitor_th(t_args *philo_args, int i)
{
	pthread_mutex_lock(&philo_args->sim_end_mtx);
	philo_args->sim_should_end = 1;
	pthread_mutex_unlock(&philo_args->meal_time_mtx);
	ft_join_philos(philo_args, i);
	ft_free_philos(philo_args);
	ft_destroy_mtxs(philo_args, philo_args->num_philo);
	ft_error(ERROR_CREATE_TH);
}

void	ft_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}
