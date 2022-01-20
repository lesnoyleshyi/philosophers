/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:37:29 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:21:10 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_simulation(void *params)
{
	t_philo			*philo_struct;

	philo_struct = (t_philo *)params;
	if (philo_struct->id % 2 == 1)
		ft_precise_sleep(philo_struct->data->eat_t);
	while (philo_struct->lunch_count < philo_struct->data->lunches)
	{
		ft_take_forks(philo_struct);
		ft_eat(philo_struct);
		ft_sleep(philo_struct);
		if (philo_struct->lunch_count >= philo_struct->data->lunches)
			return (NULL);
		ft_think(philo_struct);
	}
	return (NULL);
}

void	ft_take_forks(t_philo *philo_struct)
{
	pthread_mutex_lock(philo_struct->r_fork);
	printf("%lld %d has taken a fork\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
	pthread_mutex_lock(philo_struct->l_fork);
	printf("%lld %d has taken a fork\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
}

void	ft_eat(t_philo *philo_struct)
{
	philo_struct->lunch_count += 1;
	philo_struct->last_lunch = ft_ms_from_start(philo_struct);
	printf("%lld %d is eating\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
	ft_precise_sleep(philo_struct->data->eat_t);
	pthread_mutex_unlock(philo_struct->r_fork);
	pthread_mutex_unlock(philo_struct->l_fork);
}

void	ft_sleep(t_philo *philo_struct)
{
	printf("%lld %d is sleeping\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
	ft_precise_sleep(philo_struct->data->sleep_t);
}

void	ft_think(t_philo *philo_struct)
{
	printf("%lld %d is thinking\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
}
