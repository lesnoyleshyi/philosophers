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

void	*ft_watch(void *philo_struct)
{
	t_philo		*ph_struct;
	t_data		*data;

	ph_struct = (t_philo *) philo_struct;
	data = (ph_struct->data_struct);
	while (1)
	{
		if (ph_struct->lunch_count == data->lunches)
		{
			ft_precise_sleep(data->die_t);
			exit(EXIT_SUCCESS);
		}
		if ((ft_ms_from_start(ph_struct) - ph_struct->last_lunch) > data->die_t)
		{
			sem_wait(data->printer);
			printf("%lld %d died\n",
				ft_ms_from_start(ph_struct), ph_struct->id);
			exit(EXIT_SUCCESS);
		}
		usleep(1000);
	}
}
