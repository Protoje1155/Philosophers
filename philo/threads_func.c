/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <mkoster@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:36:50 by mkoster           #+#    #+#             */
/*   Updated: 2024/07/30 17:02:23 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_philo == 1)
	{
		pthread_create(&table->philo[0].thread_id, NULL, one_philo,
			&table->philo[0]);
		pthread_create(&table->mon_thread_id, NULL, monitor_thread, table);
		update_last_meal(&table->philo[0]);
		set_int(&table->mtx_table, &table->threads_ready, 1);
		table->start_time = gettime();
	}
	else
	{
		while (++i < table->num_philo)
			pthread_create(&table->philo[i].thread_id, NULL, dinner_simulation,
				&table->philo[i]);
		pthread_create(&table->mon_thread_id, NULL, monitor_thread, table);
		table->start_time = gettime();
		set_int(&table->mtx_table, &table->threads_ready, 1);
		i = -1;
		while (++i < table->num_philo)
			update_last_meal(&table->philo[i]);
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_philo != 1)
	{
		while (++i < table->num_philo)
			pthread_join(table->philo[i].thread_id, NULL);
		pthread_join(table->mon_thread_id, NULL);
	}
	else
	{
		pthread_join(table->philo[0].thread_id, NULL);
		pthread_join(table->mon_thread_id, NULL);
	}
}

void	*dinner_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchro_threads(philo->table);
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat / 2);
	while (!stopped(philo->table))
	{
		if (!stopped(philo->table))
			eat(philo);
		if (!stopped(philo->table))
			ft_sleep(philo);
		if (!stopped(philo->table))
			think(philo);
	}
	return (NULL);
}

void	*monitor_thread(void *arg)
{
	t_table	*table;
	int		i;
	int		full_meals_counter;

	full_meals_counter = 0;
	table = (t_table *)arg;
	synchro_threads(table);
	while (!stopped(table))
	{
		i = -1;
		full_meals_counter = 0;
		while (++i < table->num_philo && !stopped(table))
		{
			if (check_philos(table, &full_meals_counter, i) == 1)
				return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}

int	check_philos(t_table *table, int *full_meals_counter, int i)
{
	if (!philo_died(&table->philo[i]))
	{
		print_die(table->philo[i].id, "died", table->start_time, table);
		set_int(&table->mtx_table, &table->stop_simulation, 1);
		return (1);
	}
	if (!all_philos_full(&table->philo[i], full_meals_counter))
	{
		set_int(&table->mtx_table, &table->stop_simulation, 1);
		return (1);
	}
	return (0);
}
