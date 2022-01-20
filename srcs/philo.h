/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:16:25 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:20:43 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct data
{
	int				philo_count;
	int				fork_count;
	long long		die_t;
	long long		eat_t;
	long long		sleep_t;
	long long		lunches;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
}			t_data;

typedef struct philosopher
{
	int				id;
	long long		lunch_count;
	pthread_t		dude;
	t_data			*data;
	long long		last_lunch;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_philo;

int				ft_get_arguments(t_data *fu, t_philo **ck, int nor, char **me);
int				ft_create_philosophers(t_philo **fuck, t_data *no, int me);
int				ft_read_argv(t_data *params, char *argv[]);
int				ft_create_mutexes(t_data *fuck, t_philo *nor, int me);
int				ft_provide_forks(t_data *fuck, int nor, t_philo *me);

long long		ft_uint_atoi(char *str);
void			ft_get_start_time(t_data *data_struct);
void			ft_precise_sleep(unsigned int milliseconds);
long long		ft_ms_from_start(t_philo *philo_struct);
unsigned int	ft_last_lunch_delta(t_philo *philo_struct);

void			ft_take_forks(t_philo *philo_struct);
void			ft_eat(t_philo *philo_struct);
void			ft_sleep(t_philo *philo_struct);
void			ft_think(t_philo *philo_struct);

void			*ft_simulation(void *params);
void			*ft_watch(void *ph_array);
int				ft_maybe_thats_all(t_philo *ph_arr);
int				ft_perror_and_return(char *error_message, int ret_val);

#endif
