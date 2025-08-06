/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:37:02 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 09:29:17 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_threads(pthread_t *monitor, t_args *philo_args)
{
	long long	sim_time;
	int			i;

	sim_time = ft_get_time_ms();
	philo_args->sim_start_time = sim_time;
	i = 0;
	while (i < philo_args->num_philo)
	{
		philo_args->philos[i].last_meal_time = sim_time;
		if (pthread_create(&philo_args->philos[i].th_philo, NULL,
				ft_philo_routine, &philo_args->philos[i]) != 0)
		{
			ft_join_philos(philo_args, i);
			ft_free_philos(philo_args);
			ft_destroy_mtxs(philo_args, philo_args->num_philo);
			ft_error(ERROR_CREATE_TH);
		}
		i++;
	}
	if (pthread_create(monitor, NULL, ft_monitor_routine, philo_args) != 0)
		ft_error_monitor_th(philo_args, i);
}

void	ft_init_philos(t_args *args)
{
	int	i;

	args->philos = malloc(sizeof(t_philo) * args->num_philo);
	if (!args->philos)
	{
		ft_destroy_mtxs(args, args->num_philo);
		ft_error(ERROR_MALLOC);
	}
	i = 0;
	while (i < args->num_philo)
	{
		args->philos[i].philo_id = i + 1;
		args->philos[i].last_meal_time = 0;
		args->philos[i].meals_eaten = 0;
		args->philos[i].has_to_eat = 0;
		args->philos[i].state = THINKING;
		args->philos[i].left_fork = &args->forks[i];
		if (args->num_philo == 1)
			args->philos[i].right_f = NULL;
		else
			args->philos[i].right_f = &args->forks[(i + 1) % args->num_philo];
		args->philos[i].args = args;
		i++;
	}
}

void	ft_init_mtxs(t_args *philo_args)
{
	int	i;

	philo_args->forks = malloc(sizeof(pthread_mutex_t) * philo_args->num_philo);
	if (!philo_args->forks)
		ft_error(ERROR_MALLOC);
	i = 0;
	while (i < philo_args->num_philo)
	{
		if (pthread_mutex_init(&philo_args->forks[i], NULL) != 0)
		{
			ft_destroy_mtxs(philo_args, i);
			ft_error(ERROR_MUTEX_INIT);
		}
		i++;
	}
	if (pthread_mutex_init(&philo_args->print_mtx, NULL) != 0)
		ft_mutex_error(philo_args);
	if (pthread_mutex_init(&philo_args->meal_time_mtx, NULL) != 0)
		ft_mutex_error(philo_args);
	if (pthread_mutex_init(&philo_args->sim_end_mtx, NULL) != 0)
		ft_mutex_error(philo_args);
}

void	ft_init_args(char **argv, t_args *philo_args)
{
	philo_args->num_philo = ft_atoi(argv[1]);
	philo_args->time_to_die = ft_atoi(argv[2]);
	philo_args->time_to_eat = ft_atoi(argv[3]);
	philo_args->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		philo_args->num_times_to_eat = 0;
	else
		philo_args->num_times_to_eat = ft_atoi(argv[5]);
	philo_args->sim_start_time = 0;
	philo_args->sim_should_end = 0;
	philo_args->forks = NULL;
	philo_args->philos = NULL;
	if ((philo_args->num_philo <= 0 || philo_args->num_philo > 200)
		|| philo_args->time_to_die <= 0
		|| philo_args->time_to_eat <= 0
		|| philo_args->time_to_sleep <= 0
		|| (argv[5] && philo_args->num_times_to_eat <= 0))
		ft_error(ERROR_ARGS);
}
