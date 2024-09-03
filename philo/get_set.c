/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:50:49 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:50:50 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(pthread_mutex_t *mtx, int *dest, int val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

int	get_int(pthread_mutex_t *mtx, int *dest)
{
	int	val;

	pthread_mutex_lock(mtx);
	val = *dest;
	pthread_mutex_unlock(mtx);
	return (val);
}

long	get_long(pthread_mutex_t *mtx, long *dest)
{
	long	val;

	pthread_mutex_lock(mtx);
	val = *dest;
	pthread_mutex_unlock(mtx);
	return (val);
}

void	set_long(pthread_mutex_t *mtx, long *dest, long val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_last_meal);
	philo->last_meal = gettime();
	pthread_mutex_unlock(&philo->mtx_last_meal);
}
