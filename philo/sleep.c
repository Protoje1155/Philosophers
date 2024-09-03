/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:51:14 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:51:15 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	print_action(philo->id, "is sleeping", philo->table->start_time,
		philo->table);
	usleep(philo->table->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_action(philo->id, "is thinking", philo->table->start_time,
		philo->table);
	if (philo->id % 2 != 0 && philo->table->time_to_eat / 2
		+ philo->table->time_to_eat
		+ philo->table->time_to_sleep < philo->table->time_to_die)
		usleep((philo->table->time_to_eat * 500));
}
