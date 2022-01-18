/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:02:20 by stycho            #+#    #+#             */
/*   Updated: 2022/01/17 11:02:22 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

unsigned int	ft_time_delta(t_philo *philo_struct)
{
	struct timeval	now;
	long long		now_mcs;
	long long		start_mcs;
	long long		res_ms;

	gettimeofday(&now, NULL);
	start_mcs = philo_struct->data->start_time.tv_sec * 1000000
		+ philo_struct->data->start_time.tv_usec;
	now_mcs = now.tv_sec * 1000000
		+ now.tv_usec;
	res_ms = (now_mcs - start_mcs) / 1000;
	return (res_ms);
}

void	ft_precise_sleep(unsigned int milliseconds)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		if ((now.tv_sec * 1000 + now.tv_usec / 1000)
			- (start.tv_sec * 1000 + start.tv_usec / 1000) >= milliseconds)
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

int	ft_perror_and_return(char *error_message, int ret_val)
{
	printf("Programm failed with the next error message:\n%s\n", error_message);
	return (ret_val);
}
