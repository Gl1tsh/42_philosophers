/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:53:39 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/23 14:03:09 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
#define YELLOW_TEXT "\x1B[33m"
#define RESET_TEXT "\x1B[0m"

void	eat(t_philo *philo)
{
	// printf("timestamp_in_ms %d has taken a %sfork%s\n", philos->id, YELLOW_TEXT, RESET_TEXT);
	printf("%ld %d is %seating%s\n", get_time_in_ms(), philo->id, YELLOW_TEXT, RESET_TEXT);
	usleep(philo->time_to_eat * 1000);
}

void	nap(t_philo *philo)
{
	printf("%ld %d is %ssleeping%s\n", get_time_in_ms(), philo->id, RED_TEXT, RESET_TEXT);
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printf("%ld %d is %sthinking%s\n", get_time_in_ms(), philo->id, GREEN_TEXT, RESET_TEXT);
	usleep(philo->time_to_think * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo = arg;
	// action des philosophers
	usleep(philo->id * 150 * 1000);
	while (1)
	{
		eat(philo);
		nap(philo);
		think(philo);
	}
	return NULL;
}
