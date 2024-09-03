/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <mkoster@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:00:48 by mkoster           #+#    #+#             */
/*   Updated: 2024/07/30 15:48:58 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_for_errors(argc, argv) != 0)
		return (1);
	init_table(&table, argv, argc);
	start_threads(&table);
	join_threads(&table);
	free_structs(&table);
	return (0);
}
