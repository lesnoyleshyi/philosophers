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
	struct timeval	start_time;
}			t_data;

typedef struct philosopher
{
	int			id;
	pthread_t	dude;
	t_data		*data;
}				philo_t;


int			ft_get_arguments(t_data *params, philo_t **ph_arr, int argc, char *argv[]);
void		ft_get_start_time(t_data *data_struct);
int			ft_create_mutexes(t_data *params);
long long	ft_uint_atoi(char *str);


#endif
