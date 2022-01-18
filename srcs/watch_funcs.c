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

	unsigned int	death_delta;
	struct timeval	time;
	struct timeval	time_bef;

	ph_arr = (t_philo *) ph_array;
	data = (ph_arr[0].data);
	usleep(data->die_t * 1000);
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			gettimeofday(&time_bef, NULL);
			death_delta = ft_last_lunch_time_delta(&ph_arr[i]);
			gettimeofday(&time, NULL);
			if (ph_arr[i].lunch_count < data->lunches && death_delta > data->die_t)
			{
				pthread_mutex_lock(data->printer);
				printf("%u %d died\n", ft_time_delta(&ph_arr[i]) , i + 1);
				printf("%u - death delta\n", death_delta);
				printf("philo №%d\n", i + 1);
				printf("particularly now:	%ld:%d\n", time_bef.tv_sec, time_bef.tv_usec);
				printf("now: 			%ld:%d\n", time.tv_sec, time.tv_usec);
				printf("last lunch	time:	%ld:%d\n", ph_arr[i].last_lunch.tv_sec, ph_arr[i].last_lunch.tv_usec);
				printf("start 		time:	%ld:%d\n", ph_arr[i].data->start_time.tv_sec, ph_arr[i].data->start_time.tv_usec);
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
//		printf("№%d same time starts eat and being checked!\n", philo_struct->id);
//		printf("ts: %ld:%d\n", now.tv_sec, now.tv_usec);
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
	int i;
	int	philo_count;
	int	finished_eating_count;

	if (ph_arr[0].data->lunches == 0)
		return (0);
	if (ph_arr[0].data->lunches == -1488)
		return (1);
	finished_eating_count = 0;
	philo_count = ph_arr[0].data->philo_count;
	i = 0;
	while (i < philo_count)
	{
		if (ph_arr[i].lunch_count >= ph_arr[0].data->lunches)
			finished_eating_count += 1;
		i++;
	}
	if (finished_eating_count == philo_count)
	{
		ft_precise_sleep(ph_arr[0].data->eat_t);
		return (0);
	}
	return (1);
}
