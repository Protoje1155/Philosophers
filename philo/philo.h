/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <mkoster@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:56:29 by mkoster           #+#    #+#             */
/*   Updated: 2024/08/07 14:31:16 by mkoster          ###   ########.fr       */
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

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mtx_fork;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*first_fork;
	t_fork			*sec_fork;
	pthread_mutex_t	mtx_last_meal;
	pthread_mutex_t	mtx_eat;
	int				num_meals_eaten;
	int				is_eating;
	long			last_meal;
	pthread_t		thread_id;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				threads_ready;
	int				meals_to_eat;
	pthread_mutex_t	mtx_table;
	pthread_mutex_t	mtx_print;
	pthread_t		mon_thread_id;
	t_fork			*fork;
	t_philo			*philo;
	unsigned long	start_time;
	int				stop_simulation;
}	t_table;

// main functions

void	free_structs(t_table *p);
int		philo_died(t_philo *philo);

// helper functions

int		ft_strlen(char *s);
int		ft_atoi(const char *nptr);
// init functions
void	init_structs(t_table *table);
void	init_table(t_table *table, char **argv, int argc);
void	assign_forks(t_philo *philo, t_fork *fork, int i);
long	gettime(void);
void	init_philo_struct(t_philo *philo, int i, t_table *table);
void	init_table_struct(t_table *table, char **argv, int argc);

//error functions
void	print_error(char *s);
int		ft_atoi_error(char *nptr);
int		check_for_errors(int argc, char **argv);
int		check_num(char **argv, int argc);
int		check_integer(char **argv, int argc);
//thread functions
void	start_threads(t_table *pro);
void	join_threads(t_table *pro);
void	*dinner_simulation(void *arg);
void	safe_mutex_destroyer(t_table *table, int i, int flag);
void	*monitor_thread(void *arg);
void	*one_philo(void *arg);
int		all_philos_full(t_philo *philo, int *full_meals_counter);
int		check_philos(t_table *table, int *full_meals_counter, int i);
//eat functions
void	pick_up_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	eat(t_philo *philo);
//sleep and think
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);

//general actions
void	print_action(int philo_id, const char *action,
			unsigned long start_time, t_table *table);
void	print_die(int philo_id, const char *action,
			unsigned long start_time, t_table *table);
//set get mutex
int		get_int(pthread_mutex_t *mtx, int *dest);
void	set_int(pthread_mutex_t *mtx, int *dest, int val);
int		stopped(t_table *table);
void	set_long(pthread_mutex_t *mtx, long *dest, long val);
long	get_long(pthread_mutex_t *mtx, long *dest);
void	update_last_meal(t_philo *philo);
void	update_meals(t_philo *philo);
// synchro threads
void	synchro_threads(t_table *table);
#endif
