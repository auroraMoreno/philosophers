/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:23:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/24 10:53:46 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


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