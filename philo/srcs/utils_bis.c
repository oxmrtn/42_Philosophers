/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:46:37 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 11:54:43 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	send_message(t_each *data, char *str)
{
	size_t	actual_time;
	size_t	timestemp;

	actual_time = get_current_time();
	timestemp = actual_time - data->time;
	pthread_mutex_lock(data->print_m);
	printf("%zu %d %s\n", timestemp, data->i + 1, str);
	pthread_mutex_unlock(data->print_m);
}

void	send_message_main(t_philo *data, char *str, int i)
{
	size_t	actual_time;
	size_t	timestemp;

	actual_time = get_current_time();
	timestemp = actual_time - data->time;
	pthread_mutex_lock(&data->print_m);
	printf("%zu %d %s\n", timestemp, i + 1, str);
	pthread_mutex_unlock(&data->print_m);
}

int	wedead(t_each *data)
{
	pthread_mutex_lock(data->deadmutex);
	if (*data->arewedead == 1)
		return (pthread_mutex_unlock(data->deadmutex), 1);
	else
		return (pthread_mutex_unlock(data->deadmutex), 0);
}

int	everyone_ate(t_philo *data)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	if (data->numberofmeal <= 0)
		return (0);
	while (i < data->philo)
	{
		if (data->threads[i].weate >= data->numberofmeal)
			counter += 1;
		i++;
	}
	if (counter == data->philo)
		return (1);
	else
		return (0);
}

void	free_all(t_philo *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->tab);
	while (i < data->philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	free(data->fork_tab);
	i = 0;
	while (i < data->philo)
	{
		pthread_mutex_destroy(&data->threads[i].reset);
		i++;
	}
	free(data->threads);
}
