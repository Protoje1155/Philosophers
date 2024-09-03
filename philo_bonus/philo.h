/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <mkoster@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:56:29 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/07 14:38:17 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ERROR_ARG_MESSAGE "Program needs 4-5 arguments!\n"
# define ERROR_INT_MESSAGE "Arguments should correspond to integer\n"
# define ERROR_NAN_MESSAGE "Arguments must be positive numbers!\n"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				num_meals_eaten;
	long			last_meal;
	t_table			*table;
	int				pid_id;
	pthread_t		thread_id;
	int				full;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				threads_ready;
	int				meals_to_eat;
	t_philo			*philo;
	unsigned long	start_time;
	sem_t			*forks;
	sem_t			*stop;
	sem_t			*print;
	sem_t			*full_death;
	sem_t			*increment;
	pthread_t		mon_id;
}	t_table;

//init
void	init(t_table *table, char **argv, int argc);
void	wait_and_finish(t_table *table);
void	init_philo(t_table *table);
void	init_semaphores(t_table *table);
void	init_table(t_table *table, char **argv, int argc);
//error
void	print_error(char *s);
int		check_for_errors(int argc, char **argv);
int		check_num(char **argv, int argc);
int		check_integer(char **argv, int argc);
int		ft_atoi_error(char *nptr);
//helper
int		ft_atoi(const char *nptr);
void	print_sem(int id, char *s, t_table *table);
long	gettime(void);
int		ft_strlen(char *s);
int		same_string(char *a, char *b);
//process
void	start_processes(t_table *table);
void	philosopher_process(t_philo *philo);
int		philo_died_process(t_philo *philo);
int		all_philos_full_process(t_philo *philo);
void	one_process(t_philo *philo);
void	create_processes(t_table *table, int i);
//actions
void	ft_sleep_sem(t_philo *philo);
void	think_sem(t_philo *philo);
void	eat_sem(t_philo *philo);
//threads
void	*monitor(void *arg);
void	*end_checker(void *arg);
#endif
