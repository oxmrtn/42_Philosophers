/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:08:45 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 11:51:46 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

//	Assert that the input are numbers
static int	checker(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

//	Parse the input and fill the struct
int	parser(int argc, char **argv, t_philo *data)
{
	if (argc > 6 || argc < 5 || checker(argv) == 0)
		return (0);
	data->philo = ft_atoi(argv[1]);
	data->timetodie = (size_t)ft_atoi(argv[2]);
	data->timetoeat = ft_atoi(argv[3]);
	data->timetosleep = ft_atoi (argv[4]);
	data->arewedead = 0;
	if (argc == 6)
	{
		data->numberofmeal = ft_atoi(argv[5]);
		if (data->numberofmeal <= 0)
			return (0);
	}
	else
		data->numberofmeal = -1;
	if (data->philo <= 0 || data->timetodie <= 0)
		return (0);
	return (1);
}
