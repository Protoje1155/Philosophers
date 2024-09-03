/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:52:37 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/05 15:52:38 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_for_errors(argc, argv) != 0)
		return (1);
	init(&table, argv, argc);
	start_processes(&table);
	sem_wait(table.stop);
	wait_and_finish(&table);
	return (0);
}
