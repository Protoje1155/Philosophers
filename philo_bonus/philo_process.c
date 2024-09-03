/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:52:46 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 16:10:00 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_processes(t_table *table)
{
	int	i;

	i = -1;
	sem_wait(table->stop);
	if (table->num_philo != 1)
	{
		pthread_create(&table->mon_id, NULL, monitor, table);
		pthread_detach(table->mon_id);
	}
	table->start_time = gettime();
	while (++i < table->num_philo)
		create_processes(table, i);
}

void	create_processes(t_table *table, int i)
{
	table->philo[i].last_meal = gettime();
	table->philo[i].pid_id = fork();
	if (table->philo[i].pid_id == -1)
		exit(EXIT_FAILURE);
	if (table->num_philo != 1)
	{
		if (table->philo[i].pid_id == 0)
		{
			philosopher_process(&table->philo[i]);
			exit(0);
		}
	}
	else
	{
		if (table->philo[i].pid_id == 0)
		{
			one_process(&table->philo[i]);
			exit(0);
		}
	}
}

void	one_process(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_sem(philo->id, "has taken a fork", philo->table);
	usleep(philo->table->time_to_die * 1000);
	print_sem(philo->id, "is dead", philo->table);
	sem_post(philo->table->stop);
}

void	philosopher_process(t_philo *philo)
{
	int	run;

	if (philo->id % 2 == 1)
		usleep(philo->table->time_to_eat * 500);
	run = 1;
	pthread_create(&philo->thread_id, NULL, end_checker, philo);
	pthread_detach(philo->thread_id);
	usleep(100);
	while (run)
	{
		eat_sem(philo);
		ft_sleep_sem(philo);
		think_sem(philo);
	}
}
