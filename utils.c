/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:23:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/31 12:27:46 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*ejemplo:
timestamp_in_ms X has taken a fork
if should print es 1 y sim should end tmb es que un philo ha muerto 
y tenemos q pintar el mensaje de muerte
si no pues todo normal 
*/
void ft_print_msg(char *msg, t_philo *philo, int should_print)
{
    long long ts; 
    pthread_mutex_lock(&philo->args->sim_end_mtx);
    if(philo->args->sim_should_end && !should_print)
    {
        pthread_mutex_unlock(&philo->args->sim_end_mtx);
        return ; //review this
    }
    pthread_mutex_unlock(&philo->args->sim_end_mtx);
    ts = ft_get_time_ms() - philo->args->sim_start_time;
    pthread_mutex_lock(&philo->args->print_mtx);
    if(!ft_check_simulation(philo->args) || should_print)
        printf("%lld %d %s \n", ts, philo->philo_id, msg);
    pthread_mutex_unlock(&philo->args->print_mtx);
}

size_t ft_strlen(char *str)
{
    size_t i;
    
    i = 0;
    while(str[i])
        i++;

    return (i);
}

int ft_isdigit(char c)
{
    if(c >= '0' && c <= '9')
        return (1);
        
    return (0);
}

int	ft_atoi(char *str)
{
	long	res;

	res = 0;
    //is space
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
    
	while (*str)
	{
        if(!ft_isdigit(*str))
            ft_error(ERROR_NOT_NUMBER);
		res = (res * 10) + (*str - '0');
		str++;
	}
    
	return (res);
}