/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:53:39 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/26 16:58:57 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	eat(t_philo *philo)
{
	int	should_die;

	// printf("timestamp_in_ms %d has taken a %sfork%s\n", philos->id, YELLOW_TEXT, RESET_TEXT);
	if (philo->id == 1)
	{
		pthread_mutex_lock(&philo->forks[philo->id % philo->number_of_philo]);
		printf("%ld %d grab a fork (left)\n",get_time_in_ms(), philo->id);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		printf("%ld %d grab a fork (right)\n",get_time_in_ms(), philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		printf("%ld %d grab a fork (left)\n",get_time_in_ms(), philo->id);
		pthread_mutex_lock(&philo->forks[philo->id % philo->number_of_philo]);
		printf("%ld %d grab a fork (right)\n",get_time_in_ms(), philo->id);
	}
	printf("%ld %d is %seating%s\n", get_time_in_ms(), philo->id, YELLOW_TEXT, RESET_TEXT);
	philo->last_time_eat = get_time_in_ms();
	should_die = wait_or_die(philo->time_to_eat, philo);
	pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->forks[philo->id % philo->number_of_philo]);
	return (should_die);
}

int	nap(t_philo *philo)
{
	printf("%ld %d is %ssleeping%s\n", get_time_in_ms(), philo->id, RED_TEXT, RESET_TEXT);
	return (wait_or_die(philo->time_to_sleep, philo));
}

int	think(t_philo *philo)
{
	printf("%ld %d is %sthinking%s\n", get_time_in_ms(), philo->id, GREEN_TEXT, RESET_TEXT);
	return (wait_or_die(philo->time_to_think, philo));
}

void	*philo_routine(void *arg)
{
	t_philo		*philo = arg;
	// action des philosophers
	philo->last_time_eat = get_time_in_ms();
	while (1)
	{
		if (eat(philo))
			return (NULL);
		if (nap(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
	}
	return (NULL);
}
