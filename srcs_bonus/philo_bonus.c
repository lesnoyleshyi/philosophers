/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stycho <stycho@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:46:53 by stycho            #+#    #+#             */
/*   Updated: 2022/01/20 22:22:23 by stycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data_struct;
	int		ret;
	int		i;

	ft_get_arguments(&data_struct, argc, argv);
	i = -1;
	while (++i < data_struct.philo_count)
	{
		data_struct.pid_arr[i] = fork();
		if (data_struct.pid_arr[i] == 0)
		{
			ft_run_instance(&data_struct.ph_arr[i], &data_struct);
		}
	}
	wait(&ret);
	i = -1;
	while (++i < data_struct.philo_count)
	{
		kill(data_struct.pid_arr[i], 9);
	}
	free(data_struct.pid_arr);
	free(data_struct.ph_arr);
	return (0);
}

void	ft_run_instance(t_philo *philo_struct, t_data *data_struct)
{
	ft_simulation(philo_struct, data_struct);
	exit(EXIT_SUCCESS);
}
