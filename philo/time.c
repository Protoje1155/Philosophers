/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:51:28 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:51:29 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(int philo_id, const char *action, unsigned long start_time,
		t_table *table)
{
	unsigned long	elapsed_time;
	unsigned long	curr;
	int				stop;

	stop = get_int(&table->mtx_table, &table->stop_simulation);
	if (stop == 0)
	{
		curr = gettime();
		elapsed_time = curr - start_time;
		pthread_mutex_lock(&table->mtx_print);
		printf("%lu %d %s\n", elapsed_time, philo_id, action);
		pthread_mutex_unlock(&table->mtx_print);
	}
}

void	print_die(int philo_id, const char *action, unsigned long start_time,
		t_table *table)
{
	unsigned long	elapsed_time;
	unsigned long	curr;

	curr = gettime();
	elapsed_time = curr - start_time;
	pthread_mutex_lock(&table->mtx_print);
	printf("%lu %d %s\n", elapsed_time, philo_id, action);
	pthread_mutex_unlock(&table->mtx_print);
}

long	gettime(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	philo_died(t_philo *philo)
{
	long	e;
	long	t;

	e = gettime() - get_long(&philo->mtx_last_meal, &philo->last_meal);
	t = philo->table->time_to_die;
	if (t <= e && !philo->is_eating)
		return (0);
	else
		return (1);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchro_threads(philo->table);
	print_action(philo->id, "has taken a fork", philo->table->start_time,
		philo->table);
	while (!stopped(philo->table))
		usleep(10);
	return (NULL);
}
