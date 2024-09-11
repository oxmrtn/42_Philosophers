/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:30:46 by mtrullar          #+#    #+#             */
/*   Updated: 2024/08/16 12:30:46 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_nk
{
	int	i;
	int	j;
}				t_nk;

typedef struct s_each
{
	pthread_mutex_t	**fork;
	pthread_mutex_t	*tab;
	pthread_mutex_t	*print_m;
	pthread_mutex_t	*deadmutex;
	pthread_mutex_t	reset;
	pthread_t		threads;
	size_t			timetodie;
	size_t			timetolive;
	size_t			time;
	int				*arewedead;
	int				*fork_tab;
	int				i;
	int				timetoeat;
	int				timetosleep;
	int				numberofmeal;
	int				weate;
	int				philo;
}				t_each;

typedef struct s_philo
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	deadmutex;
	pthread_mutex_t	print_m;
	pthread_mutex_t	tab;
	t_each			*threads;
	size_t			timetodie;
	size_t			time;
	int				*fork_tab;
	int				arewedead;
	int				philo;
	int				timetoeat;
	int				timetosleep;
	int				numberofmeal;
}			t_philo;

//	PARSING
int			parser(int argc, char **argv, t_philo *data);

//	UTILS
size_t		get_current_time(void);
int			copy_data(t_philo *data, t_each *each, int i);
int			ft_usleep(size_t milliseconds);
int			everyone_ate(t_philo *data);
int			ft_atoi(const char *nptr);
int			wedead(t_each *data);
int			ft_isdigit(int c);
void		send_message_main(t_philo *data, char *str, int i);
void		send_message(t_each *data, char *str);
void		free_all(t_philo *data);

//	FREE FUNC ERROR
void		destroy_mutex_till_i(t_philo *data, int i);
void		free_mutex_and_shit(t_philo *data);
void		destroy_mutex_fork(t_philo *data);

//	INIT PHILO
int			create_philo(t_philo *data);

//	ROUTINE
void		*routine(void *data);
void		*monitor(void *arg);

//	STATES
void		reset_fork(t_each *data);
void		dream(t_each *data);
void		think(t_each *data);
void		eat(t_each *data);
int			may_i_fork(t_each *data);

#endif
