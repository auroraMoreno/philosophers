/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:23:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/07/17 09:59:10 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_check_avoid_dying(t_args *args)
{
    // si son impares
    if(args->num_philo % 2 != 0)
    {
        if(args->time_to_die < (args->time_to_eat + args->time_to_sleep + 10))
            ft_error("Not enough time to eat, philo will die.");  //de momento error pero preguntar jeje  
    }
    else if(args->num_philo % 2 == 0)  //si son pares 
    {
        if(args->time_to_die < (args->time_to_eat * 2 + args->time_to_sleep + 10))
            ft_error("Not enough time to eat, philo will die."); 
    }
    
}

/*ejemplo:
timestamp_in_ms X has taken a fork
*/
void ft_print_msg(char *msg, int philo_id)
{
    long ts; 
    ts = ft_get_time_ms();
    printf("%ld %d %s \n", ts, philo_id, msg);
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