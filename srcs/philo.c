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

void	*simulation(void *params);
void	*ft_watch(void *ph_array);

int	main(int argc, char *argv[])
{
	pthread_t	watcher;
	philo_t		*ph_arr;
	t_data 		params;
	int			i;
	int			ret;

	if (ft_get_arguments(&params, &ph_arr, argc, argv) == 1)
	{
		printf("Error in parsing params\n");
		return (1);
	}
	else
	{
		printf("parsing params ok\n");
	}
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
//		printf("Thread №%d has been joined!\n", i + 1);
		if (ret != 0)
		{
			printf("Error joining threads\n");
			return (1);
		}
	}
	return (0);
}

int	ft_get_arguments(t_data *params, philo_t **ph_arr, int argc, char *argv[])
{
	if (argc > 6 || argc < 5)
		return (1);
	if (ft_read_argv(params, argv) == 1)
		return (1);
	if (ft_create_philosophers(ph_arr, params, params->philo_count) == 1)
		return (1);
	if (ft_create_mutexes(params, *ph_arr, params->fork_count) == 1)
		return (1);
	return (0);
}

void	ft_get_start_time(t_data *data_struct)
{
	if (data_struct->start_time.tv_sec == 0)
		gettimeofday(&(data_struct->start_time), NULL);
}

void	*ft_watch(void *ph_array)
{
	philo_t			*ph_arr;
	t_data			*data;
	int				i;
	struct timeval	now;

	ph_arr = (philo_t *) ph_array;
	data = (ph_arr[0].data);
	usleep(data->die_t * 1000 + 100);
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			printf("check %d philo\n", i + 1);
			gettimeofday(&now, NULL);
			if ((now.tv_sec * 1000 + now.tv_usec / 1000)
			- (ph_arr[i].last_lunch.tv_sec * 1000 + ph_arr[i].last_lunch.tv_usec / 1000) > data->die_t)
			{
				pthread_mutex_lock(data->printer);
				printf("%lu %d died\n", (now.tv_sec * 1000 + now.tv_usec / 1000)
				- (ph_arr[i].data->start_time.tv_sec * 1000 + ph_arr[i].data->start_time.tv_usec / 1000), i + 1);
				return (NULL);
			}
			else
				printf("works\n");
		}
	}
}