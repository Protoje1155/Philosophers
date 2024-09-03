/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <mkoster@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:27:41 by mkoster           #+#    #+#             */
/*   Updated: 2024/07/30 17:02:00 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, t_fork *fork, int i)
{
	int	philo_num;

	philo_num = philo->table->num_philo;
	if ((philo->id - 1) % 2 == 0)
	{
		philo->first_fork = &fork[i];
		philo->sec_fork = &fork[(i + 1) % philo_num];
	}
	else
	{
		philo->first_fork = &fork[(i + 1) % philo_num];
		philo->sec_fork = &fork[i];
	}
}

void	init_structs(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philo)
	{
		philo = table->philo + i;
		init_philo_struct(philo, i, table);
		if (pthread_mutex_init(&table->philo[i].mtx_eat, NULL) != 0)
		{
			safe_mutex_destroyer(table, i, 3);
			return ;
		}
		if (pthread_mutex_init(&table->fork[i].mtx_fork, NULL) != 0)
		{
			safe_mutex_destroyer(table, i, 0);
			return ;
		}
		if (pthread_mutex_init(&table->philo[i].mtx_last_meal, NULL) != 0)
		{
			safe_mutex_destroyer(table, i, 1);
			return ;
		}
		assign_forks(philo, table->fork, i);
	}
}

void	init_table(t_table *table, char **argv, int argc)
{
	init_table_struct(table, argv, argc);
	if (pthread_mutex_init(&table->mtx_table, NULL) != 0)
	{
		safe_mutex_destroyer(table, 1, 2);
		return ;
	}
	if (pthread_mutex_init(&table->mtx_print, NULL) != 0)
	{
		safe_mutex_destroyer(table, 1, 4);
		return ;
	}
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->num_philo);
	if (table->philo == NULL)
		return ;
	table->fork = (t_fork *)malloc(table->num_philo * sizeof(t_fork));
	if (table->fork == NULL)
	{
		free(table->philo);
		return ;
	}
	init_structs(table);
}

void	init_philo_struct(t_philo *philo, int i, t_table *table)
{
	philo->table = table;
	philo->id = i + 1;
	philo->last_meal = 0;
	philo->is_eating = 0;
	philo->num_meals_eaten = 0;
	table->fork[i].id = i;
}

void	init_table_struct(t_table *table, char **argv, int argc)
{
	table->num_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_to_eat = ft_atoi(argv[5]);
	else
		table->meals_to_eat = -1;
	table->threads_ready = 0;
	table->stop_simulation = 0;
}
