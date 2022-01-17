/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:37:29 by stycho            #+#    #+#             */
/*   Updated: 2022/01/16 13:37:30 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation(void *params)
{
	t_philo			*philo_struct;

	philo_struct = (t_philo *)params;
	while (1)
	{
		ft_take_forks(philo_struct);
		ft_eat(philo_struct);
		ft_sleep(philo_struct);
		ft_think(philo_struct);
	}
}

void	ft_take_forks(t_philo *philo_struct)
{
	if (philo_struct->id % 2 == 0)
	{
		pthread_mutex_lock(philo_struct->r_fork);
		printf("%u %d has taken a fork\n",
			   ft_time_delta(philo_struct), philo_struct->id);
		pthread_mutex_lock(philo_struct->l_fork);
		printf("%u %d has taken a fork\n",
			   ft_time_delta(philo_struct), philo_struct->id);
	}
	else
	{
		pthread_mutex_lock(philo_struct->l_fork);
		printf("%d %d has taken a fork\n",
			   ft_time_delta(philo_struct), philo_struct->id);
		pthread_mutex_lock(philo_struct->r_fork);
		printf("%d %d has taken a fork\n",
			   ft_time_delta(philo_struct), philo_struct->id);
	}
}

void	ft_eat(t_philo *philo_struct)
{
	philo_struct->lunch_count += 1;
	gettimeofday(&philo_struct->last_lunch, NULL);
	printf("%d %d is eating\n", ft_time_delta(philo_struct), philo_struct->id);
	ft_precise_sleep(philo_struct->data->eat_t);
	pthread_mutex_unlock(philo_struct->r_fork);
	pthread_mutex_unlock(philo_struct->l_fork);
}

void	ft_sleep(t_philo *philo_struct)
{
	printf("%d %d is sleeping\n",
		ft_time_delta(philo_struct), philo_struct->id);
	ft_precise_sleep(philo_struct->data->sleep_t);
}

void	ft_think(t_philo *philo_struct)
{
	printf("%d %d is thinking\n",
		ft_time_delta(philo_struct), philo_struct->id);
}
