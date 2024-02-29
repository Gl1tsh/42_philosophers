/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:10 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/29 12:22:15 by nagiorgi         ###   ########.fr       */
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

int	should_die(t_philo *philo)
{
	if (philo->table->stop)
		return (1);
	if (get_time_in_ms() > (philo->last_time_eat + philo->time_to_die))
	{
		printf("%s%ld %d died%s\n", RYT, get_time_in_ms(),
			philo->id, RXT);
		philo->table->stop = 1;
		return (1);
	}
	return (0);
}

int	wait_or_die(int time_to_wait, t_philo *philo)
{
	long	start_time;

	if (should_die(philo))
		return (1);
	start_time = get_time_in_ms();
	while (get_time_in_ms() < (start_time + time_to_wait))
	{
		usleep(250);
		if (should_die(philo))
			return (1);
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

int	take_one_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->forks[fork_id]);
	if (should_die(philo) != 0)
	{
		pthread_mutex_unlock(&philo->forks[fork_id]);
		return (1);
	}
	printf("%ld %d grab a fork %d\n", get_time_in_ms(), philo->id, fork_id + 1);
	return (0);
}
