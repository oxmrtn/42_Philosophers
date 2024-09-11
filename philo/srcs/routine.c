/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:54:24 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 11:54:27 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

static void	sd(t_philo *data)
{
	pthread_mutex_lock(&data->deadmutex);
	data->arewedead = 1;
	pthread_mutex_unlock(&data->deadmutex);
}

void	*routine(void *arg)
{
	t_each	*data;

	data = (t_each *)arg;
	while (!wedead(data))
	{
		eat(data);
		dream(data);
		think(data);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*data;
	int		i;

	ft_usleep(5);
	i = 0;
	data = (t_philo *)arg;
	while (1 == 1)
	{
		while (i < data->philo)
		{
			pthread_mutex_lock(&(data->threads[i].reset));
			if ((get_current_time() - data->threads[i].timetolive
					> data->timetodie) || everyone_ate(data))
			{
				if (!everyone_ate(data))
					send_message_main(data, "died", i);
				return (sd(data),
					pthread_mutex_unlock(&(data->threads[i].reset)), NULL);
			}
			pthread_mutex_unlock(&(data->threads[i].reset));
			i++;
		}
		i = 0;
	}
	return (NULL);
}
