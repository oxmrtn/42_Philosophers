/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:20:47 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 11:52:52 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

int	create_mutex(t_philo *data)
{
	int	i;

	i = 0;
	data->fork_tab = malloc(sizeof(int) * (data->philo));
	data->fork = malloc(sizeof(pthread_mutex_t) * (data->philo));
	if (!data->fork || !data->fork_tab)
		return (write(2, "Error", 5), 0);
	while (i < data->philo)
	{
		data->fork_tab[i] = 0;
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (destroy_mutex_till_i(data, i), 0);
		i++;
	}
	if (pthread_mutex_init(&data->tab, NULL) != 0)
		return (destroy_mutex_fork(data), 0);
	if (pthread_mutex_init(&data->print_m, NULL) != 0)
		return (destroy_mutex_fork(data), pthread_mutex_destroy(&data->tab), 0);
	if (pthread_mutex_init(&data->deadmutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_m);
		return (destroy_mutex_fork(data), pthread_mutex_destroy(&data->tab), 0);
	}
	return (1);
}

int	create_everyting(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->philo)
	{
		copy_data(data, &data->threads[i], i);
		i++;
	}
	return (1);
}

int	create_philo(t_philo *data)
{
	pthread_t		monitoring;
	int				i;

	i = -1;
	data->threads = malloc(sizeof(t_each) * (data->philo));
	if (create_mutex(data) == 0)
		return (free(data->threads), 0);
	data->time = get_current_time();
	if (create_everyting(data) == 0)
		return (free_mutex_and_shit(data), 0);
	pthread_create(&monitoring, NULL, &monitor, data);
	while (++i < data->philo)
		if (pthread_create(&data->threads[i].threads, NULL,
				&routine, &data->threads[i]) != 0)
			return (0);
	i = 0;
	while (i < data->philo)
	{
		if (pthread_join(data->threads[i].threads, NULL) != 0)
			return (0);
		i++;
	}
	pthread_join(monitoring, NULL);
	return (1);
}
