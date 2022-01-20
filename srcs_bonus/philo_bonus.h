/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:16:25 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:22:30 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <signal.h>
# include "string.h"
# include "semaphore.h"

typedef struct data
{
	int					philo_count;
	int					fork_count;
	long long			die_t;
	long long			eat_t;
	long long			sleep_t;
	long long			lunches;
	sem_t				*printer;
	sem_t				*forks;
	pid_t				*pid_arr;
	struct timeval		start_time;
	struct philosopher	*ph_arr;
}			t_data;

typedef struct philosopher
{
	int				id;
	pid_t			*pid_addr;
	long long		lunch_count;
	long long		last_lunch;
	t_data			*data_struct;
}				t_philo;

void			ft_perror_and_exit(char *message);

int				ft_get_arguments(t_data *params, int argc, char *argv[]);
int				ft_read_argv(t_data *data_struct, char *argv[]);
int				ft_create_philosophers(pid_t **pid_arr, t_data *data_struct);
int				ft_create_semaphores(t_data *data_struct, int fork_count);

long long		ft_uint_atoi(char *str);
void			ft_get_start_time(t_data *data_struct);
void			ft_precise_sleep(unsigned int milliseconds);
long long		ft_ms_from_start(t_philo *philo_struct);
unsigned int	ft_last_lunch_delta(t_philo *philo_struct);

void			ft_simulation(t_philo *philo_struct, t_data *data_struct);
void			ft_run_instance(t_philo *philo_struct, t_data *data_struct);
void			*ft_watch(void *ph_array);
int				ft_maybe_thats_all(t_philo *ph_arr);

void			ft_take_forks(t_philo *philo_struct);
void			ft_eat(t_philo *philo_struct);
void			ft_sleep(t_philo *philo_struct);
void			ft_think(t_philo *philo_struct);

#endif
