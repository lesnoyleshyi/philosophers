/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_funcs_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 13:37:29 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:22:51 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_simulation(t_philo *philo_struct, t_data *data_struct)
{
	int			ret;
	pthread_t	watcher_thread;

	ft_get_start_time(data_struct);
	ret = pthread_create(&watcher_thread, NULL, ft_watch, philo_struct);
	if (ret != 0)
		ft_perror_and_exit("Error creating watcher thread");
	if (philo_struct->id % 2 == 1)
		ft_precise_sleep(data_struct->eat_t);
	while (philo_struct->lunch_count < data_struct->lunches)
	{
		ft_take_forks(philo_struct);
		ft_eat(philo_struct);
		if (philo_struct->lunch_count >= philo_struct->data_struct->lunches)
			break ;
		ft_sleep(philo_struct);
		ft_think(philo_struct);
	}
	while (1)
		;
}

void	ft_take_forks(t_philo *philo_struct)
{
	sem_wait(philo_struct->data_struct->forks);
	printf("%lld %d has taken a fork\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
	sem_wait(philo_struct->data_struct->forks);
	printf("%lld %d has taken a fork\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
}

void	ft_eat(t_philo *philo_struct)
{
	philo_struct->lunch_count += 1;
	philo_struct->last_lunch = ft_ms_from_start(philo_struct);
	printf("%lld %d is eating\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
	ft_precise_sleep(philo_struct->data_struct->eat_t);
	sem_post(philo_struct->data_struct->forks);
	sem_post(philo_struct->data_struct->forks);
}

void	ft_sleep(t_philo *philo_struct)
{
	printf("%lld %d is sleeping\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
	ft_precise_sleep(philo_struct->data_struct->sleep_t);
}

void	ft_think(t_philo *philo_struct)
{
	printf("%lld %d is thinking\n",
		ft_ms_from_start(philo_struct), philo_struct->id);
}
