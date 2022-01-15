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
	int	philo_count;

	if (argc > 6 || argc < 5)
		return (1);
	philo_count = ft_uint_atoi(argv[1]);
	params->philo_count = philo_count;
	params->fork_count = philo_count;
	params->die_t = ft_uint_atoi(argv[2]);
	params->eat_t = ft_uint_atoi(argv[3]);
	params->sleep_t = ft_uint_atoi(argv[4]);
	params->lunches = ft_uint_atoi(argv[5]);
	*ph_arr = (philo_t *)malloc(sizeof(philo_t ) * philo_count);
 	if (philo_count == -1 || params->die_t == -1 || params->eat_t == -1
		|| params->sleep_t == -1 || params->lunches == -1)
 		return (1);
	if (*ph_arr == NULL)
		return (1);
	while (philo_count--)
	{
		(*ph_arr)[philo_count].id = philo_count + 1;
		(*ph_arr)[philo_count].data = params;
	}
	if (ft_create_mutexes(params) == 1)
		return (1);
	return (0);
}

long long	ft_uint_atoi(char *str)
{
	unsigned long long	res;

	res = 0;
	if (!str)
		return (0);
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > 9223372036854775807)
		return(-1);
	return ((long long)res);
}

void	*simulation(void *params)
{
	philo_t	*dudes_struct;

	dudes_struct = (philo_t *)params;
//	ft_eat(data);
	pthread_mutex_lock(dudes_struct->data->printer);
	printf("hello from philosopher N%d\n", dudes_struct->id);
	printf("PH %d knows that he is one of %d philosophers\n",dudes_struct->id, dudes_struct->data->philo_count);
	pthread_mutex_unlock(dudes_struct->data->printer);
	return (0);
}

//void	*ft_eat(philo_t *data)
//{
//	pthread_mutex_lock();
//	ft_take_forks();
//	ft_eat();
//}

int	ft_create_mutexes(t_data *params)
{
	pthread_mutex_t	*printer;
	int				ret;

	printer = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!printer)
		return (1);
	params->printer = printer;
	ret = pthread_mutex_init(printer, NULL);
	if (ret != 0)
		return (1);
	return (0);
}
