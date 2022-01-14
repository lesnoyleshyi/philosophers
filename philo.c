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

void	*hello(void *params);

int	main(int argc, char *argv[])
{
	struct timeval	cur_time;
	t_data 			params;
	int				i;
	int				ret;

	gettimeofday(&cur_time, NULL);
	ft_get_arguments(&params, argc, argv);
	i = 0;
	while (i < params.philo_count)
	{
		ret = pthread_create(&(params.dudes_arr[i].dude), NULL, hello, &(params.dudes_arr[i]));
		if (ret != 0)
			ft_perror_and_exit("Error creating thread!\n");
		i++;
	}
	i = 0;
	while (i < params.philo_count)
	{
		ret = pthread_join(params.dudes_arr[i].dude, NULL);
		if (ret != 0)
			ft_perror_and_exit("Error joining thread!\n");
		i++;
	}
	printf("Bye!\n");
	return (0);
}

void	ft_get_arguments(t_data *params, int argc, char *argv[])
{
	int	philo_count;

	if (argc > 6 || argc < 5)
		ft_perror_and_exit("Wrong arguments count\n");
	philo_count = ft_uint_atoi(argv[1]);
	params->philo_count = philo_count;
	params->fork_count = philo_count;
	params->die_t = ft_uint_atoi(argv[2]);
	params->eat_t = ft_uint_atoi(argv[3]);
	params->sleep_t = ft_uint_atoi(argv[4]);
	if (params->sleep_t >= 1000000)
		ft_perror_and_exit("Philosopher can't sleep more than 999999 usec\n");
	params->lunches = ft_uint_atoi(argv[5]);
	params->dudes_arr = (philo_t *)malloc(sizeof(philo_t ) * philo_count);
	if (params->dudes_arr == NULL)
		ft_perror_and_exit("Unable to allocate memory for threads\n");
	while (philo_count--)
		params->dudes_arr[philo_count - 1].id = philo_count;
}

void	ft_perror_and_exit(const char *message)
{
	int	i;

	i = 0;
	while (message[i])
		write(2, &message[i++], 1);
	exit(EXIT_FAILURE);
}

unsigned int	ft_uint_atoi(char *str)
{
	long long	res;

	res = 0;
	if (!str)
		return (0);
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-')
		ft_perror_and_exit("Arguments can't be negative\n");
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > 4294967295)
		ft_perror_and_exit("Argument can't exceed uint range\n");
	return (res);
}

void	*hello(void *params)
{
	philo_t	*data;

	data = (philo_t *)params;
	printf("hello from sniper monkey N%d\n", data->id);
	return (0);
}
