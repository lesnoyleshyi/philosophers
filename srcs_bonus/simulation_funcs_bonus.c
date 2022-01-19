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

#include "philo_bonus.h"

void	ft_simulation(t_philo *philo_struct, t_data *data_struct)
{
	if (philo_struct)
		ft_precise_sleep(data_struct->eat_t);
	while (philo_struct->lunch_count < data_struct->lunches)
	{
		ft_take_forks(philo_struct);
		ft_eat(philo_struct);
		ft_sleep(philo_struct);
		if (philo_struct->lunch_count >= philo_struct->data_struct->lunches)
			exit(EXIT_SUCCESS);
		ft_think(philo_struct);
	}
	exit(EXIT_SUCCESS);
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
