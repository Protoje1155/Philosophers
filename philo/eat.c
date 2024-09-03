/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:50:30 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:50:36 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
	{
		pthread_mutex_lock(&philo->first_fork->mtx_fork);
		pthread_mutex_lock(&philo->sec_fork->mtx_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->first_fork->mtx_fork);
		pthread_mutex_lock(&philo->sec_fork->mtx_fork);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->mtx_fork);
	pthread_mutex_unlock(&philo->sec_fork->mtx_fork);
}

void	eat(t_philo *philo)
{
	pick_up_forks(philo);
	print_action(philo->id, "has taken a fork", philo->table->start_time,
		philo->table);
	print_action(philo->id, "has taken a fork", philo->table->start_time,
		philo->table);
	print_action(philo->id, "is eating", philo->table->start_time,
		philo->table);
	update_last_meal(philo);
	usleep(philo->table->time_to_eat * 1000);
	update_meals(philo);
	release_forks(philo);
}
