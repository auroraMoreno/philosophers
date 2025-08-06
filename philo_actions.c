/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:26:33 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 09:53:19 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_msg(TAKEN_FORK, philo, 0);
		pthread_mutex_lock(philo->right_f);
		ft_print_msg(TAKEN_FORK, philo, 0);
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		ft_print_msg(TAKEN_FORK, philo, 0);
		pthread_mutex_lock(philo->left_fork);
		ft_print_msg(TAKEN_FORK, philo, 0);
	}
}

void	ft_drop_forks(t_philo *philo)
{
	if (philo->right_f)
		pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_eat(t_philo *philo)
{
	if (ft_check_simulation(philo->args))
		return ;
	philo->state = EATING;
	ft_print_msg(IS_EATING, philo, 0);
	pthread_mutex_lock(&philo->args->meal_time_mtx);
	philo->last_meal_time = ft_get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->args->meal_time_mtx);
	ft_my_usleep(philo->args->time_to_eat, philo->args);
	ft_drop_forks(philo);
	philo->state = SLEEPING;
}

void	ft_sleep(t_philo *philo)
{
	if (ft_check_simulation(philo->args))
		return ;
	ft_print_msg(IS_SLEEPING, philo, 0);
	ft_my_usleep(philo->args->time_to_sleep, philo->args);
}

void	ft_think(t_philo *philo)
{
	long long	thinking_time;
	long long	meal_time_passed;

	if (ft_check_simulation(philo->args))
		return ;
	ft_print_msg(IS_THINKING, philo, 0);
	if (philo->args->num_philo > 1
		&& philo->args->time_to_eat > philo->args->time_to_sleep)
	{
		thinking_time = (philo->args->time_to_eat - philo->args->time_to_sleep);
		thinking_time = thinking_time / 2;
		if (thinking_time <= 0)
			thinking_time = 1;
		pthread_mutex_lock(&philo->args->meal_time_mtx);
		meal_time_passed = ft_get_time_ms() - philo->last_meal_time;
		pthread_mutex_unlock(&philo->args->meal_time_mtx);
		if (meal_time_passed + thinking_time < philo->args->time_to_die)
			ft_my_usleep(thinking_time, philo->args);
	}
}
