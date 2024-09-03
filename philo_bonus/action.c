/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:51:57 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:51:58 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep_sem(t_philo *philo)
{
	print_sem(philo->id, "is sleeping", philo->table);
	usleep(philo->table->time_to_sleep * 1000);
}

void	think_sem(t_philo *philo)
{
	print_sem(philo->id, "is thinking", philo->table);
	if (philo->id % 2 != 0 && philo->table->time_to_eat / 2
		+ philo->table->time_to_eat
		+ philo->table->time_to_sleep < philo->table->time_to_die)
		usleep((philo->table->time_to_eat * 500));
}

void	eat_sem(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_sem(philo->id, "has taken a fork", philo->table);
	sem_wait(philo->table->forks);
	print_sem(philo->id, "has taken a fork", philo->table);
	print_sem(philo->id, "is eating", philo->table);
	philo->last_meal = gettime();
	usleep(philo->table->time_to_eat * 1000);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	philo->num_meals_eaten++;
}

int	philo_died_process(t_philo *philo)
{
	long	e;
	long	t;

	e = gettime() - philo->last_meal;
	t = philo->table->time_to_die;
	if (t <= e)
	{
		print_sem(philo->id, "is dead", philo->table);
		return (0);
	}
	return (1);
}

int	all_philos_full_process(t_philo *philo)
{
	if (philo->table->meals_to_eat != -1)
	{
		if (philo->num_meals_eaten >= philo->table->meals_to_eat)
			return (0);
	}
	return (1);
}
