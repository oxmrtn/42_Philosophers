/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:34:05 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 13:11:13 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

int	may_i_fork(t_each *data)
{
	pthread_mutex_lock(data->tab);
	if (data->philo == 1)
		return (pthread_mutex_unlock(data->tab), 0);
	if (data->i == 0)
	{
		if (data->fork_tab[data->philo - 1] == 0 && data->fork_tab[0] == 0)
		{
			data->fork_tab[data->philo - 1] = 1;
			data->fork_tab[0] = 1;
			return (pthread_mutex_unlock(data->tab), 1);
		}
		else
			return (pthread_mutex_unlock(data->tab), 0);
	}
	else
	{
		if (data->fork_tab[data->i - 1] == 0 && data->fork_tab[data->i] == 0)
		{
			data->fork_tab[data->i - 1] = 1;
			data->fork_tab[data->i] = 1;
			return (pthread_mutex_unlock(data->tab), 1);
		}
		else
			return (pthread_mutex_unlock(data->tab), 0);
	}
}

void	reset_fork(t_each *data)
{
	pthread_mutex_lock(data->tab);
	if (data->i == 0)
	{
		data->fork_tab[data->philo - 1] = 0;
		data->fork_tab[0] = 0;
		pthread_mutex_unlock(data->tab);
	}
	else
	{
		data->fork_tab[data->i - 1] = 0;
		data->fork_tab[data->i] = 0;
		pthread_mutex_unlock(data->tab);
	}
}

void	eat(t_each *data)
{
	t_nk	fork;

	if (may_i_fork(data) == 1 && !wedead(data))
	{
		if (data->i == 0)
			fork.i = data->philo - 1;
		else
			fork.i = data->i - 1;
		fork.j = data->i;
		pthread_mutex_lock(&(*data->fork)[fork.i]);
		pthread_mutex_lock(&(*data->fork)[fork.j]);
		send_message(data, "has taken a fork");
		pthread_mutex_lock(&(data->reset));
		data->timetolive = get_current_time();
		pthread_mutex_unlock(&(data->reset));
		send_message(data, "is eating");
		ft_usleep(data->timetoeat);
		data->weate++;
		pthread_mutex_unlock(&(*data->fork)[fork.i]);
		pthread_mutex_unlock(&(*data->fork)[fork.j]);
		return (reset_fork(data));
	}
	if (wedead(data))
		return ;
	return (usleep(50), eat(data));
}

void	dream(t_each *data)
{
	if (!wedead(data))
	{
		send_message(data, "is sleeping");
		ft_usleep(data->timetosleep);
	}
}

void	think(t_each *data)
{
	if (!wedead(data))
	{
		send_message(data, "is thinking");
		if (data->philo % 2 == 0 && data->philo < 50)
			usleep(1);
		else
			usleep(500);
	}
}
