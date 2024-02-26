/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/27 00:12:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	wait_or_die(int time_to_wait, t_philo *philo)
{
	int	time_spend;
	int	small_nap;

	time_spend = 0;
	while (time_spend < time_to_wait)
	{
		if (time_to_wait - time_spend < 10)
			small_nap = time_to_wait - time_spend;
		else
			small_nap = 10;
		usleep(small_nap * 1000);
		time_spend += small_nap;
		if (get_time_in_ms() > (philo->last_time_eat + philo->time_to_die))
		{
			printf("%s%ld %d died%s\n", RYT, get_time_in_ms(),
				philo->id, RYT);
			return (1);
		}
	}
	return (0);
}

int	ft_atoi_custom(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (-1);
	return (result);
}
