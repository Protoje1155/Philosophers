/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:51:04 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:51:06 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// flag = 0 forks, flag = 1 lastmeals...
void	safe_mutex_destroyer(t_table *table, int i, int flag)
{
	int	j;

	j = -1;
	if (flag == 0 || flag == 1 || flag == 3)
	{
		while (++j < i)
		{
			if (flag == 0)
				pthread_mutex_destroy(&table->fork[j].mtx_fork);
			else if (flag == 1)
				pthread_mutex_destroy(&table->philo[j].mtx_last_meal);
			else if (flag == 3)
				pthread_mutex_destroy(&table->philo[j].mtx_eat);
		}
		free(table->philo);
		free(table->fork);
	}
	if (flag == 2)
		pthread_mutex_destroy(&table->mtx_table);
	if (flag == 4)
		pthread_mutex_destroy(&table->mtx_print);
}

void	free_structs(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		pthread_mutex_destroy(&table->fork[i].mtx_fork);
		pthread_mutex_destroy(&table->philo[i].mtx_last_meal);
		pthread_mutex_destroy(&table->philo[i].mtx_eat);
	}
	pthread_mutex_destroy(&table->mtx_table);
	pthread_mutex_destroy(&table->mtx_print);
	free(table->philo);
	free(table->fork);
}
