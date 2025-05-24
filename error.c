/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:56:35 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/24 10:55:17 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_error(char *str)
{
    write(STDERR_FILENO, str, ft_strlen(str));
    exit(EXIT_FAILURE);
}