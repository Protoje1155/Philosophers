/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:52:24 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:52:25 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_table *table, char **argv, int argc)
{
	init_table(table, argv, argc);
	init_semaphores(table);
	init_philo(table);
}

void	init_philo(t_table *table)
{
	int	i;

	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->num_philo);
	if (table->philo == NULL)
		return ;
	i = -1;
	while (++i < table->num_philo)
	{
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].last_meal = 0;
		table->philo[i].num_meals_eaten = 0;
		table->philo[i].pid_id = -1;
		table->philo[i].full = 0;
	}
}

void	init_semaphores(t_table *table)
{
	sem_unlink("stop");
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("full_death");
	sem_unlink("increment");
	table->stop = sem_open("stop", O_CREAT, 0644, 1);
	table->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, table->num_philo);
	table->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	table->full_death = sem_open("full_death", O_CREAT | O_EXCL, 0644, 1);
	table->increment = sem_open("increment", O_CREAT | O_EXCL, 0644, 1);
}

void	init_table(t_table *table, char **argv, int argc)
{
	table->num_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_to_eat = ft_atoi(argv[5]);
	else
		table->meals_to_eat = -1;
}

void	wait_and_finish(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
		kill(table->philo[i].pid_id, 9);
	sem_close(table->stop);
	sem_unlink("stop");
	sem_close(table->forks);
	sem_unlink("forks");
	sem_close(table->print);
	sem_unlink("print");
	sem_close(table->full_death);
	sem_unlink("full_death");
	sem_close(table->increment);
	sem_unlink("increment");
	free(table->philo);
}
