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

#include "philo_bonus.h"

void	*ft_watch(void *ph_array)
{
	t_philo			*ph_arr;
	t_data			*data;
	int				i;
	long long int	death_time_ms;

	ph_arr = (t_philo *) ph_array;
	data = (ph_arr[0].data_struct);

	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			death_time_ms = ft_ms_from_start(&ph_arr[i]);
			if (ph_arr[i].lunch_count < data->lunches
			&& ft_ms_from_start(&ph_arr[i]) - ph_arr[i].last_lunch > data->die_t)
			{
				sem_wait(data->printer);
				printf("%lld %d died\n", ft_ms_from_start(&ph_arr[i]), i + 1);
				printf("Death_time_ms:\t\t%lld\n", death_time_ms);
				printf("Last lunch time_ms: \t%lld\n", ph_arr[i].last_lunch);
				return (NULL);
			}
		}
		if (ft_maybe_thats_all(ph_arr) == 0)
			return (NULL);
	}
}

int	ft_maybe_thats_all(t_philo *ph_arr)
{
	int	i;
	int	philo_count;
	int	finished_eating_count;

	finished_eating_count = 0;
	philo_count = ph_arr[0].data_struct->philo_count;
	i = 0;
	while (i < philo_count)
	{
		if (ph_arr[i].lunch_count == ph_arr[0].data_struct->lunches)
			finished_eating_count += 1;
		i++;
	}
	if (finished_eating_count == philo_count)
	{
		ft_precise_sleep(ph_arr[0].data_struct->eat_t - 10);
		return (0);
	}
	return (1);
}
