/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:15:01 by stycho            #+#    #+#             */
/*   Updated: 2022/01/13 13:15:02 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_t	watcher;
	t_philo		*ph_arr;
	t_data 		params;
	int			i;
	int			ret;

	if (ft_get_arguments(&params, &ph_arr, argc, argv) == 1)
	{
		printf("Error in parsing params\n");
		return (1);
	}
//	else
//	{
//		printf("parsing params ok\n");
//	}
	i = -1;
	ft_get_start_time(&params);
	while (++i < params.philo_count)
	{
		ret = pthread_create(&ph_arr[i].dude, NULL, simulation, &ph_arr[i]);
		if (ret != 0)
		{
			printf("Error creating threads\n");
			return (1);
		}
	}
	ret = pthread_create(&watcher, NULL, ft_watch, ph_arr);
	ret = pthread_join(watcher, NULL);
	if (ret == 0)
		return (0);
	i = -1;
	while (++i < params.philo_count)
	{
		ret = pthread_join(ph_arr[i].dude, NULL);
		printf("Thread №%d has been joined!\n", i + 1);
		if (ret != 0)
		{
			printf("Error joining threads\n");
			return (1);
		}
	}
	return (0);
}
