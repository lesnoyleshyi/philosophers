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

unsigned int	ft_time_delta(philo_t *philo_struct);
unsigned int	ft_last_lunch_delta(philo_t *philo_struct);
void	ft_take_forks(philo_t *philo_struct);
void	ft_eat(philo_t *philo_struct);
void	ft_sleep(philo_t *philo_struct);
void	ft_think(philo_t *philo_struct);

void	*simulation(void *params)
{
	philo_t			*philo_struct;
//	struct timeval	now;

	philo_struct = (philo_t *)params;
	while (1)
	{
		ft_take_forks(philo_struct);
		ft_eat(philo_struct);
		ft_sleep(philo_struct);
		ft_think(philo_struct);
		gettimeofday(&philo_struct->now, NULL);
		if (ft_time_delta(philo_struct) > philo_struct->data->die_t
		|| ft_last_lunch_delta(philo_struct) > philo_struct->data->die_t)
		{
//			pthread_mutex_lock(dudes_struct->data->printer);
			printf("%d %d died\n", ft_time_delta(philo_struct), philo_struct->id);
			return (NULL);
		}
	}
}


unsigned int	ft_time_delta(philo_t *philo_struct)
{
	long long	now_ms;
	long long	start_ms;

	start_ms = philo_struct->data->start_time.tv_sec * 1000
			+ philo_struct->data->start_time.tv_usec / 1000;
	now_ms = philo_struct->now.tv_sec * 1000
			+ philo_struct->now.tv_usec / 1000;
	return ((unsigned int)(now_ms - start_ms));
}

unsigned int	ft_last_lunch_delta(philo_t *philo_struct)
{
	long long	now_ms;
	long long	last_lunch_ms;

	last_lunch_ms = philo_struct->last_lunch.tv_sec * 1000
			+ philo_struct->last_lunch.tv_usec / 1000;
	now_ms = philo_struct->now.tv_sec * 1000
			+ philo_struct->now.tv_usec / 1000;
	return ((unsigned int)(now_ms - last_lunch_ms));
}

void	ft_eat(philo_t *philo_struct)
{
	pthread_mutex_lock(philo_struct->data->boil);
	gettimeofday(&philo_struct->now, NULL);
	printf("%d %d is eating\n", ft_time_delta(philo_struct), philo_struct->id);
	usleep(philo_struct->data->eat_t * 1000);
	gettimeofday(&philo_struct->last_lunch, NULL);
	pthread_mutex_unlock(philo_struct->data->boil);
	pthread_mutex_unlock(philo_struct->r_fork);
	pthread_mutex_unlock(philo_struct->l_fork);
}

void	ft_sleep(philo_t *philo_struct)
{
	gettimeofday(&philo_struct->now, NULL);
	printf("%d %d is sleeping\n", ft_time_delta(philo_struct), philo_struct->id);
	usleep(philo_struct->data->sleep_t * 1000);
}

void	ft_take_forks(philo_t *philo_struct)
{
	if (philo_struct->id % 2 == 0)
	{
		pthread_mutex_lock(philo_struct->r_fork);
		gettimeofday(&philo_struct->now, NULL);
		printf("%u %d has taken a fork\n", ft_time_delta(philo_struct), philo_struct->id);
		pthread_mutex_lock(philo_struct->l_fork);
		gettimeofday(&philo_struct->now, NULL);
		printf("%u %d has taken a fork\n", ft_time_delta(philo_struct), philo_struct->id);
	}
	else
	{
		pthread_mutex_lock(philo_struct->l_fork);
		gettimeofday(&philo_struct->now, NULL);
		printf("%d %d has taken a fork\n", ft_time_delta(philo_struct), philo_struct->id);
		pthread_mutex_lock(philo_struct->r_fork);
		gettimeofday(&philo_struct->now, NULL);
		printf("%d %d has taken a fork\n", ft_time_delta(philo_struct), philo_struct->id);
	}
}

void	ft_think(philo_t *philo_struct)
{
	gettimeofday(&philo_struct->now, NULL);
	printf("%d %d is thinking\n", ft_time_delta(philo_struct), philo_struct->id);
}
