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

void	ft_precise_sleep(unsigned int milliseconds)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		if ((now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000) > milliseconds)
			return ;
		else
			usleep(10);
	}
}
