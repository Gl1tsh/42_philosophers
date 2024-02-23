/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/23 16:42:48 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

long	get_time_in_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	wait_or_die(int time_to_wait, t_philo *philo)
{
	int	time_spend;

	time_spend = 0;
	while (time_to_wait > time_spend)
	{
		usleep(10 * 1000);
		time_spend += 10;
		if (get_time_in_ms() > (philo->last_time_eat + philo->time_to_die))
		{
			printf("%s%ld %d died%s\n",RED_TEXT, get_time_in_ms(), philo->id, RESET_TEXT);
			return (1);
		}
	}
	return (0);
}
