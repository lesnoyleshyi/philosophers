/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:02:20 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:22:40 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_uint_atoi(char *str)
{
	unsigned long long	res;

	res = 0;
	if (!str)
		return (-2);
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
		return (-1);
	return ((long long)res);
}

long long	ft_ms_from_start(t_philo *philo_struct)
{
	struct timeval	now;
	long long		now_mcs;
	long long		start_mcs;

	gettimeofday(&now, NULL);
	start_mcs = philo_struct->data_struct->start_time.tv_sec * 1000000
		+ philo_struct->data_struct->start_time.tv_usec;
	now_mcs = now.tv_sec * 1000000
		+ now.tv_usec;
	return ((now_mcs - start_mcs) / 1000);
}

void	ft_precise_sleep(unsigned int milliseconds)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		if ((now.tv_sec * 1000000 + now.tv_usec)
			- (start.tv_sec * 1000000 + start.tv_usec) >= (milliseconds * 1000))
			return ;
		else
			usleep(500);
	}
}

void	ft_get_start_time(t_data *data_struct)
{
	if (data_struct->start_time.tv_sec == 0)
		gettimeofday(&(data_struct->start_time), NULL);
}

void	ft_perror_and_exit(char *message)
{
	int	i;

	i = 0;
	while (message[i])
		write(2, &message[i++], 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
