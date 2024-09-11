/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:30:09 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/28 11:51:34 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	data;

	if (parser(argc, argv, &data) == 0)
		return (printf("Error\n"), 1);
	if (create_philo(&data) == 0)
		return (printf("Error\n"), 1);
	free_all(&data);
	return (0);
}
