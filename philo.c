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

int	main(int argc, char *argv[])
{
	struct timeval	cur_time;
	philo_t			*ph_arr;
	t_data 			params;
	int				i;
	int				ret;

	if (ft_get_arguments(&params, &ph_arr, argc, argv) == 1)
	{
		printf("Error in parsing params\n");
		return (1);
	}
	i = -1;
	while (++i < params.philo_count)
	{
		ret = pthread_create(&ph_arr[i].dude, NULL, simulation, &ph_arr[i]);
		if (ret != 0)
		{
			printf("Error creating threads\n");
			return (1);
		}
	}
	i = -1;
	while (++i < params.philo_count)
	{
		ret = pthread_join(ph_arr[i].dude, NULL);
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


void	*simulation(void *params)
{
	philo_t			*dudes_struct;
	struct timeval	now;

	dudes_struct = (philo_t *)params;
	ft_get_start_time(dudes_struct->data);
//	ft_eat(data);
	while (1)
	{
		if (dudes_struct->id % 2 == 0)
		{
			pthread_mutex_lock(dudes_struct->r_fork);
			gettimeofday(&now, NULL);
			printf("%ld.%d\t%d\thas taken right fork\n",
				   now.tv_sec - dudes_struct->data->start_time.tv_sec,
				   now.tv_usec - dudes_struct->data->start_time.tv_usec,
				   dudes_struct->id);
			pthread_mutex_lock(dudes_struct->l_fork);
			gettimeofday(&now, NULL);
			printf("%ld.%d\t%d\thas taken left fork\n",
				   now.tv_sec - dudes_struct->data->start_time.tv_sec,
				   now.tv_usec - dudes_struct->data->start_time.tv_usec,
				   dudes_struct->id);
		}
		else
		{
			pthread_mutex_lock(dudes_struct->l_fork);
			gettimeofday(&now, NULL);
			printf("%ld.%d\t%d\thas taken left fork\n",
				   now.tv_sec - dudes_struct->data->start_time.tv_sec,
				   now.tv_usec - dudes_struct->data->start_time.tv_usec,
				   dudes_struct->id);
			pthread_mutex_lock(dudes_struct->r_fork);
			gettimeofday(&now, NULL);
			printf("%ld.%d\t%d\thas taken right fork\n",
				   now.tv_sec - dudes_struct->data->start_time.tv_sec,
				   now.tv_usec - dudes_struct->data->start_time.tv_usec,
				   dudes_struct->id);
		}
		pthread_mutex_lock(dudes_struct->data->boil);
		gettimeofday(&now, NULL);
		printf("%ld.%d\t%d\tis eating\n",
			   now.tv_sec - dudes_struct->data->start_time.tv_sec,
			   now.tv_usec - dudes_struct->data->start_time.tv_usec,
			   dudes_struct->id);
		usleep(dudes_struct->data->eat_t * 1000);
		pthread_mutex_unlock(dudes_struct->data->boil);
		pthread_mutex_unlock(dudes_struct->r_fork);
		pthread_mutex_unlock(dudes_struct->l_fork);
		gettimeofday(&now, NULL);
		printf("%ld.%d\t%d\tis sleeping\n",
			   now.tv_sec - dudes_struct->data->start_time.tv_sec,
			   now.tv_usec - dudes_struct->data->start_time.tv_usec,
			   dudes_struct->id);
		usleep(dudes_struct->data->sleep_t * 1000);
		gettimeofday(&now, NULL);
		printf("%ld.%d\t%d\tis thinking\n",
			   now.tv_sec - dudes_struct->data->start_time.tv_sec,
			   now.tv_usec - dudes_struct->data->start_time.tv_usec,
			   dudes_struct->id);
		gettimeofday(&now, NULL);
		if (now.tv_sec - dudes_struct->data->start_time.tv_sec > dudes_struct->data->die_t)
		{
			printf("%ld.%d\t%d\tdied\n",
				   now.tv_sec - dudes_struct->data->start_time.tv_sec,
				   now.tv_usec - dudes_struct->data->start_time.tv_usec,
				   dudes_struct->id);
			break;
		}
	}
	return (0);
}

//void	*ft_eat(philo_t *data)
//{
//	pthread_mutex_lock();
//	ft_take_forks();
//	ft_eat();
//}

void	ft_get_start_time(t_data *data_struct)
{
	if (data_struct->start_time.tv_sec == 0)
		gettimeofday(&(data_struct->start_time), NULL);
}
