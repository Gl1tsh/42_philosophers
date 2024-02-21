/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:30:24 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/21 17:19:24 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
#define YELLOW_TEXT "\x1B[33m"
#define RESET_TEXT "\x1B[0m"

long	get_time_in_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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

int	main(int argc, char **argv)
{
	int				i;
	int				number_of_philo;
	t_philo			*philos;

	number_of_philo = 5;

	// allocation pour le nombre de philosopher
	philos = malloc(sizeof(t_philo) * number_of_philo);
	if (philos == NULL)
		return (1);

	// Creation de chaque chaque thread philosopher
	i = 0;
	while (i < number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].time_to_eat = 200;
		philos[i].time_to_sleep = 400;
		philos[i].time_to_think = 800;
		pthread_create(&philos[i].thread_id, NULL, philo_routine, &philos[i]);
		i++;
	}

	// Attente que les thread philo finissent pour quitter sans les tuer
	i = 0;
	while (i < number_of_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}