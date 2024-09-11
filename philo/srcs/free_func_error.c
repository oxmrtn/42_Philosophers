/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:58:36 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 12:01:18 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	destroy_mutex_fork(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	free(data->fork_tab);
	return ;
}

void	destroy_mutex_till_i(t_philo *data, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&data->fork[j]);
		j++;
	}
	free(data->fork);
	free(data->fork_tab);
	return ;
}

void	free_mutex_and_shit(t_philo *data)
{
	int	i;

	i = 0;
	destroy_mutex_till_i(data, data->philo);
	while (i < data->philo)
	{
		pthread_mutex_destroy(&data->threads[i].reset);
		i++;
	}
	free(data->threads);
	return ;
}
