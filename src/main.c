/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:30:24 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/23 13:56:45 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

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