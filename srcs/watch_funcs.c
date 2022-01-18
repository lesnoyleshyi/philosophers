/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:45:16 by stycho            #+#    #+#             */
/*   Updated: 2022/01/17 18:45:17 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_watch(void *ph_array)
{
	t_philo			*ph_arr;
	t_data			*data;
	int				i;

	ph_arr = (t_philo *) ph_array;
	data = (ph_arr[0].data);
	usleep(data->die_t * 1000);
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (ph_arr[i].lunch_count < data->lunches
				&& ft_last_lunch_time_delta(&ph_arr[i]) > data->die_t)
			{
				pthread_mutex_lock(data->printer);
				printf("%u %d died\n", ft_time_delta(&ph_arr[i]), i + 1);
				return (NULL);
			}
		}
		if (ft_maybe_thats_all(ph_arr) == 0)
			return (NULL);
	}
}

unsigned int	ft_last_lunch_time_delta(t_philo *philo_struct)
{
	struct timeval	now;
	long long		now_mcs;
	long long		last_lunch_mcs;

	gettimeofday(&now, NULL);
	if (philo_struct->last_lunch.tv_sec == now.tv_sec
		&& philo_struct->last_lunch.tv_usec == now.tv_usec)
	{
		return (0);
	}
	last_lunch_mcs = philo_struct->last_lunch.tv_sec * 1000000
		+ philo_struct->last_lunch.tv_usec;
	now_mcs = now.tv_sec * 1000000
		+ now.tv_usec;
	if (last_lunch_mcs >= now_mcs)
		return (0);
	else
		return ((now_mcs - last_lunch_mcs) / 1000);
}

int	ft_maybe_thats_all(t_philo *ph_arr)
{
	int	i;
	int	philo_count;
	int	finished_eating_count;

	finished_eating_count = 0;
	philo_count = ph_arr[0].data->philo_count;
	i = 0;
	while (i < philo_count)
	{
		if (ph_arr[i].lunch_count == ph_arr[0].data->lunches)
			finished_eating_count += 1;
		i++;
	}
	if (finished_eating_count == philo_count)
	{
		ft_precise_sleep(ph_arr[0].data->eat_t - 10);
		return (0);
	}
	return (1);
}
