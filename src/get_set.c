/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/07 12:40:54 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_char_mutex(pthread_mutex_t *mutex, char *to_change, char value)
{
	pthread_mutex_lock(mutex);
	*to_change = value;
	pthread_mutex_unlock(mutex);
}

char	get_char_mutex(pthread_mutex_t *mutex, char variable)
{
	char value;

	pthread_mutex_lock(mutex);
	value = variable;
	pthread_mutex_unlock(mutex);
	return (value);
}

long get_time(char time_type)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (time_type == SECONDS)
		return(time.tv_sec + time.tv_usec / 1000000);
	else if (time_type == MILLISECONDS)
		return(time.tv_sec * 1000 + time.tv_usec / 1000);
	else if (time_type == USECS)
		return(time.tv_sec * 1000000 + time.tv_usec);
	else
		exit_error("Wrong time type!");
	return (0);
}

void	my_own_usleep(long time_usec, t_all *base)
{
	long start;

	start = get_time(USECS);
	while(get_time(USECS) - start < time_usec)
	{
		if (get_char_mutex(base->sim_finished_mtx, base->simulation_finished))
			return ;
		if ((get_time(USECS) - start) / 2 > 50)
			usleep((get_time(USECS) - start) / 2);
		else
		{
			while (get_time(USECS) - start < time_usec);
			usleep(1);
			return ;
		}
	}
}
