/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:51:21 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:51:23 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	synchro_threads(t_table *table)
{
	while (get_int(&table->mtx_table, &table->threads_ready) == 0)
		usleep(10);
}

int	stopped(t_table *table)
{
	return (get_int(&table->mtx_table, &table->stop_simulation));
}

int	all_philos_full(t_philo *philo, int *full_meals_counter)
{
	int	num;

	if (philo->table->meals_to_eat != -1)
	{
		num = get_int(&philo->mtx_eat, &philo->num_meals_eaten);
		if (num >= philo->table->meals_to_eat)
			*full_meals_counter += 1;
		if (*full_meals_counter == philo->table->num_philo)
			return (0);
		else
			return (1);
	}
	return (1);
}
