/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:30:24 by nagiorgi          #+#    #+#             */
/*   Updated: 2024/02/29 14:34:20 by nagiorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <string.h>

/**
 **	Allocation pour le nombre de philosopher
 **	Allocation pour le nombre de fourchette
 **	Creation de fourchettes pour philo
 **/
int	table_prepare(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	if (table->philos == NULL)
		return (1);
	memset(table->philos, 0, sizeof(t_philo) * table->number_of_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	if (table->forks == NULL)
		return (1);
	memset(table->forks, 0, sizeof(pthread_mutex_t) * table->number_of_philo);
	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1);
	return (0);
}

// Creation de chaque chaque thread philosopher
int	philo_launcher(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].number_of_philo = table->number_of_philo;
		table->philos[i].forks = table->forks;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].times_must_eat = table->times_must_eat;
		table->philos[i].times_eaten = 0;
		table->philos[i].table = table;
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine,
				&table->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 ** La fonction table_clean attend que tous les threads (philosophes)
 ** 	se terminent et détruit tous les mutex (fourchettes).
 ** Si une erreur se produit lors de l'attente d'un
 ** 	thread ou de la destruction d'un mutex, la fonction renvoie 1.
 ** Sinon, elle renvoie 0.
 **/
int	table_clean(t_table *table)
{
	int	i;

	if (table->philos)
	{
		i = 0;
		while (i < table->number_of_philo)
		{
			pthread_join(table->philos[i].thread_id, NULL);
			i++;
		}
	}
	if (table->forks)
	{
		i = 0;
		while (i < table->number_of_philo)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&table->stop_mutex);
	free(table->philos);
	free(table->forks);
	return (0);
}
/**
 ** Saisis des informations par le user
 ** et envois les data dans la struct
 **/

int	init_table(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	table->number_of_philo = ft_atoi_custom(argv[1]);
	if (table->number_of_philo == 0)
		return (1);
	if (table->number_of_philo == 1)
	{
		printf("%s%ld 1 died%s\n", RYT, get_time_in_ms(), RXT);
		return (1);
	}
	table->time_to_die = ft_atoi_custom(argv[2]);
	table->time_to_eat = ft_atoi_custom(argv[3]);
	table->time_to_sleep = ft_atoi_custom(argv[4]);
	if (argc == 6)
		table->times_must_eat = ft_atoi_custom(argv[5]);
	else
		table->times_must_eat = 0;
	table->stop = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	table.forks = NULL;
	if (init_table(argc, argv, &table) != 0)
	{
		table_clean(&table);
		return (1);
	}
	if (table_prepare(&table) != 0)
	{
		table_clean(&table);
		return (1);
	}
	philo_launcher(&table);
	table_clean(&table);
	return (0);
}
