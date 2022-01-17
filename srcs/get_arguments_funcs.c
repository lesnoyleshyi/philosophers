/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:12:30 by stycho            #+#    #+#             */
/*   Updated: 2022/01/15 20:12:33 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_arguments(t_data *params, t_philo **ph_arr, int argc, char *argv[])
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

int	ft_read_argv(t_data *params, char *argv[])
{
	int	philo_count;

	philo_count = ft_uint_atoi(argv[1]);
	params->philo_count = philo_count;
	params->fork_count = philo_count;
	params->die_t = ft_uint_atoi(argv[2]);
	params->eat_t = ft_uint_atoi(argv[3]);
	params->sleep_t = ft_uint_atoi(argv[4]);
	params->lunches = ft_uint_atoi(argv[5]);
	if (philo_count == -1 || params->die_t == -1 || params->eat_t == -1
		|| params->sleep_t == -1 || params->lunches == -1)
		return (1);
	return (0);
}

int	ft_create_philosophers(t_philo **ph_arr, t_data *data, int ph_count)
{
	*ph_arr = (t_philo *)malloc(sizeof(t_philo) * ph_count);
	if (*ph_arr == NULL)
		return (1);
	while (ph_count--)
	{
		(*ph_arr)[ph_count].id = ph_count + 1;
		(*ph_arr)[ph_count].data = data;
		(*ph_arr)[ph_count].lunch_count = 0;
		(*ph_arr)[ph_count].last_lunch.tv_sec = 0;
		(*ph_arr)[ph_count].last_lunch.tv_usec = 0;
	}
	return (0);
}

int	ft_create_mutexes(t_data *params, t_philo *ph_arr, int fork_count)
{
	pthread_mutex_t	*printer;
	pthread_mutex_t	*forks;
	int				ret;

	printer = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * fork_count);
	if (!printer || !forks)
		return (1);
	params->printer = printer;
	params->forks = forks;
	ret = pthread_mutex_init(printer, NULL);
	if (ret != 0)
		return (1);
	if (ft_provide_forks(params, params->fork_count, ph_arr) == 1)
		return (1);
	return (0);
}

int	ft_provide_forks(t_data *params, int fork_count, t_philo *ph_arr)
{
	int	ret;
	int	i;

	i = -1;
	while (++i < fork_count)
	{
		ret = pthread_mutex_init(&(params->forks[i]), NULL);
		if (ret != 0)
			return (1);
	}
	i = -1;
	while (++i < fork_count)
	{
		if (i == 0)
			ph_arr[i].r_fork = &(params->forks[fork_count - 1]);
		else
			ph_arr[i].r_fork = &(params->forks[i - 1]);
		ph_arr[i].l_fork = &(params->forks[i]);
	}
	return (0);
}
