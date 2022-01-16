/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:16:25 by stycho            #+#    #+#             */
/*   Updated: 2022/01/13 13:16:26 by stycho           ###   ########.fr       */
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
	pthread_mutex_t	*boil;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
}			t_data;

typedef struct philosopher
{
	int				id;
	pthread_t		dude;
	t_data			*data;
	struct timeval	now;
	struct timeval	last_lunch;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				philo_t;


int			ft_get_arguments(t_data *params, philo_t **ph_arr, int argc, char *argv[]);
int			ft_create_philosophers(philo_t **ph_arr, t_data *data, int ph_count);
int			ft_read_argv(t_data *params, char *argv[]);
void		ft_get_start_time(t_data *data_struct);
int			ft_create_mutexes(t_data *params, philo_t *ph_arr, int fork_count);
int			ft_provide_forks(t_data *params, int fork_count, philo_t *ph_arr);
long long	ft_uint_atoi(char *str);

unsigned int	ft_time_delta(philo_t *philo_struct);
unsigned int	ft_last_lunch_delta(philo_t *philo_struct);
void	ft_take_forks(philo_t *philo_struct);
void	ft_eat(philo_t *philo_struct);
void	ft_sleep(philo_t *philo_struct);
void	ft_think(philo_t *philo_struct);


#endif
