/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:46:53 by stycho            #+#    #+#             */
/*   Updated: 2022/01/18 19:46:54 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void		ft_perror_and_exit(char *message);
long long	ft_uint_atoi(char *str);
void		ft_test_func(long long sleep_in_ms);
void	ft_create_processes(int number_of_processes, pid_t *pid_array, long long sleep_in_ms);

int	main(int argc, char *argv[])
{
	pid_t		*pid_arr;
	int			philo_count;
	long long	sleep_in_ms;
//	int			i;
//	int 		ret;

	if (argc < 2 || argc > 4)
		ft_perror_and_exit("Wrong arguments count");

	sleep_in_ms = ft_uint_atoi(argv[2]);

	philo_count = ft_uint_atoi(argv[1]);
	pid_arr = (pid_t *) malloc(sizeof(pid_t) * philo_count);

	ft_create_processes(philo_count, pid_arr, sleep_in_ms);

//	i = -1;
//	while (++i < philo_count)
//	{
//		waitpid(pid_arr[i], &ret, WNOHANG);
//	}
	free(pid_arr);
	return (0);
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

void	ft_test_func(long long sleep_in_ms)
{
	write(1, "hello from process\n", 20);
	usleep(sleep_in_ms * 1000);
	return ;
}

void	ft_create_processes(int number_of_processes, pid_t *pid_array, long long sleep_in_ms)
{
	int i;
	int ret;

	i = -1;
	while (++i < number_of_processes)
	{
		pid_array[i] = fork();
		if (pid_array[i] == 0)
			ft_test_func(sleep_in_ms);
		else
			waitpid(pid_array[i], &ret, WNOHANG);
	}
}
