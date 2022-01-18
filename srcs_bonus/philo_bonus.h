/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:16:25 by stycho            #+#    #+#             */
/*   Updated: 2022/01/18 19:47:02 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
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



#endif
