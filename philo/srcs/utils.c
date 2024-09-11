/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:15:39 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 10:50:48 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

//	1 if c is a digit else 0
int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

//	ascii to integer
int	ft_atoi(const char *nptr)
{
	int		i;
	int		signe;
	int		result;

	i = 0;
	result = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += (nptr[i] - '0');
		i++;
	}
	return (signe * result);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	copy_data(t_philo *data, t_each *each, int i)
{
	each->i = i;
	each->timetodie = data->timetodie;
	each->numberofmeal = data->numberofmeal;
	each->timetoeat = data->timetoeat;
	each->timetosleep = data->timetosleep;
	each->fork = &data->fork;
	each->fork_tab = data->fork_tab;
	each->tab = &data->tab;
	each->philo = data->philo;
	each->time = data->time;
	each->timetolive = get_current_time();
	each->print_m = &data->print_m;
	each->arewedead = &data->arewedead;
	each->deadmutex = &data->deadmutex;
	each->weate = 0;
	if (pthread_mutex_init(&(each->reset), NULL) != 0)
		return (0);
	return (1);
}
