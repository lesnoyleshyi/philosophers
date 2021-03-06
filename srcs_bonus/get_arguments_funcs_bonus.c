/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments_funcs_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:12:30 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:22:07 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_get_arguments(t_data *data_struct, int argc, char *argv[])
{
	if (argc > 6 || argc < 5)
		ft_perror_and_exit("Wrong arguments count!");
	ft_read_argv(data_struct, argv);
	ft_create_philosophers(&(data_struct->pid_arr), data_struct);
	ft_create_semaphores(data_struct, data_struct->fork_count);
	return (0);
}

int	ft_read_argv(t_data *data_struct, char *argv[])
{
	int	philo_count;

	philo_count = ft_uint_atoi(argv[1]);
	data_struct->philo_count = philo_count;
	data_struct->fork_count = philo_count;
	data_struct->die_t = ft_uint_atoi(argv[2]);
	data_struct->eat_t = ft_uint_atoi(argv[3]);
	data_struct->sleep_t = ft_uint_atoi(argv[4]);
	data_struct->lunches = ft_uint_atoi(argv[5]);
	if (philo_count < 1 || philo_count > 256 || data_struct->die_t < 1
		|| data_struct->eat_t < 1 || data_struct->sleep_t < 1
		|| data_struct->lunches == -1)
		ft_perror_and_exit("Unsupported values in arguments");
	if (data_struct->lunches == 0)
		ft_perror_and_exit("What does it mean 'eat 0 times?'");
	if (data_struct->lunches == -2)
		data_struct->lunches = 9223372036854775807;
	return (0);
}

int	ft_create_philosophers(pid_t **pid_arr, t_data *data_struct)
{
	int	pid_count;
	int	i;

	pid_count = data_struct->philo_count;
	*pid_arr = (pid_t *) malloc(sizeof(pid_t) * pid_count);
	if (*pid_arr == NULL)
		ft_perror_and_exit("Error allocating memory for array of pids");
	memset(*pid_arr, 0, pid_count);
	data_struct->ph_arr = (t_philo *) malloc(sizeof(t_philo) * pid_count);
	if (data_struct->ph_arr == NULL)
		ft_perror_and_exit("Error allocating memory for array of philosophers");
	i = -1;
	while (++i < pid_count)
	{
		data_struct->ph_arr[i].id = i + 1;
		data_struct->ph_arr[i].last_lunch = 0;
		data_struct->ph_arr[i].lunch_count = 0;
		data_struct->ph_arr[i].data_struct = data_struct;
		data_struct->ph_arr[i].pid_addr = &((*pid_arr)[i]);
	}
	return (0);
}

int	ft_create_semaphores(t_data *data_struct, int fork_count)
{
	sem_unlink("forks");
	sem_unlink("stdout");
	data_struct->forks = sem_open("forks", O_CREAT, S_IRWXU, fork_count);
	data_struct->printer = sem_open("stdout", O_CREAT, S_IRWXU, 1);
	return (0);
}
