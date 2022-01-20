/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:15:01 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:20:31 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_t	watcher;
	t_philo		*ph_arr;
	t_data		params;
	int			i;
	int			ret;

	if (ft_get_arguments(&params, &ph_arr, argc, argv) == 1)
		return (1);
	i = -1;
	ft_get_start_time(&params);
	while (++i < params.philo_count)
	{
		ret = pthread_create(&ph_arr[i].dude, NULL, ft_simulation, &ph_arr[i]);
		if (ret != 0)
			return (ft_perror_and_return("Error creating threads", 1));
	}
	ret = pthread_create(&watcher, NULL, ft_watch, ph_arr);
	if (ret != 0)
		return (ft_perror_and_return("Error creating watcher thread", 1));
	ret = pthread_join(watcher, NULL);
	if (ret != 0)
		return (ft_perror_and_return("Error joining watcher thread", 1));
	free(params.printer);
	return (0);
}
