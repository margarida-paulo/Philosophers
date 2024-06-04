/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/04 16:00:38 by mvalerio         ###   ########.fr       */
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
	if (time_type == MILLISECONDS)
		return(time.tv_sec * 1000 + time.tv_usec / 1000);
	else
		exit_error("You didn't ask for either seconds or milliseconds!");
	return (0);
}

void	my_own_usleep(long millisec, t_all *base)
{
	long start;

	start = get_time(MILLISECONDS);
	while(get_time(MILLISECONDS) - start < millisec)
	{
		if (get_char_mutex(base->general_mutex, base->simulation_finished))
			return();
	}
}
