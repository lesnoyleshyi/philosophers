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

typedef struct philosopher
{
	int			id;
	pthread_t	dude;
}				philo_t;

typedef struct data
{
	int				philo_count;
	int				fork_count;
	unsigned int	die_t;
	unsigned int	eat_t;
	unsigned int	sleep_t;
	unsigned int	lunches;
	philo_t 		*dudes_arr;
}			t_data;

void			ft_perror_and_exit(const char *message);
void			ft_get_arguments(t_data *params, int argc, char *argv[]);
unsigned int	ft_uint_atoi(char *str);

#endif
