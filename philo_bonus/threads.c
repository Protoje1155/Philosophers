/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:52:52 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:52:53 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	int		count;
	t_table	*table;

	count = 0;
	table = (void *)arg;
	while (1)
	{
		sem_wait(table->increment);
		count++;
		if (count == table->num_philo + 1)
		{
			sem_post(table->stop);
			break ;
		}
	}
	return (0);
}

void	*end_checker(void *arg)
{
	t_philo	*philo;
	int		run;

	run = 1;
	philo = (t_philo *)arg;
	while (run)
	{
		sem_wait(philo->table->full_death);
		if (!philo_died_process(philo))
		{
			run = 0;
			sem_post(philo->table->stop);
		}
		sem_post(philo->table->full_death);
		sem_wait(philo->table->full_death);
		if (!all_philos_full_process(philo) && run != 0)
		{
			run = 0;
			sem_post(philo->table->increment);
		}
		sem_post(philo->table->full_death);
		usleep(10);
	}
	return (NULL);
}
