/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:47:49 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/06 09:35:27 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_args		philo_args;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
		ft_error(ERROR_ARGS);
	ft_init_args(argv, &philo_args);
	ft_init_mtxs(&philo_args);
	ft_init_philos(&philo_args);
	ft_init_threads(&monitor, &philo_args);
	pthread_join(monitor, NULL);
	ft_join_philos(&philo_args, philo_args.num_philo);
	ft_destroy_mtxs(&philo_args, philo_args.num_philo);
	ft_free_philos(&philo_args);
	return (0);
}
