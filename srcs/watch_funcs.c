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

unsigned int	ft_last_lunch_time_delta(t_philo *philo_struct);

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
//			printf("%u - death delta\n", death_delta);
			if (death_delta > data->die_t)
			{
				pthread_mutex_lock(data->printer);
				printf("%u %d died\n", ft_time_delta(&ph_arr[i]) , i + 1);
				printf("%u - death delta\n", death_delta);
				printf("philo №%d\n", i + 1);
				printf("particularly now:	%ld:%d\n", time_bef.tv_sec, time_bef.tv_usec);
				printf("now: 			%ld:%d\n", time.tv_sec, time.tv_usec);
				printf("last lunch	time:	%ld:%d\n", ph_arr[i].last_lunch.tv_sec, ph_arr[i].last_lunch.tv_usec);
				printf("start 		time:	%ld:%d\n", ph_arr[i].data->start_time.tv_sec, ph_arr[i].data->start_time.tv_usec);
				printf("real delta: 		%ld\n", ph_arr[i].data->start_time.tv_sec - ph_arr[i].data->start_time.tv_usec);
				return (NULL);
			}
		}
	}
}

unsigned int	ft_last_lunch_time_delta(t_philo *philo_struct)
{
	struct timeval	now;
	long long		now_mcs;
	long long		last_lunch_mcs;
//	long			sec_delta;
//	unsigned int	usec_delta;

	gettimeofday(&now, NULL);
	if (philo_struct->last_lunch.tv_sec == now.tv_sec
	&& philo_struct->last_lunch.tv_usec == now.tv_usec)
	{
		printf("№%d same time starts eat and being checked!\n", philo_struct->id);
		printf("ts: %ld:%d\n", now.tv_sec, now.tv_usec);
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
//	return ((unsigned int)(now_ms - last_lunch_ms));
//	if (philo_struct->last_lunch.tv_sec >= now.tv_sec)
//		sec_delta = philo_struct->last_lunch.tv_sec - now.tv_sec;
//	else
//		sec_delta = now.tv_sec - philo_struct->last_lunch.tv_sec;
//	if ()
}
