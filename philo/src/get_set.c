/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 16:17:27 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_int_mutex(pthread_mutex_t *mutex, int *to_change, int value)
{
	pthread_mutex_lock(mutex);
	*to_change = value;
	pthread_mutex_unlock(mutex);
}

int	get_int_mutex(pthread_mutex_t *mutex, int *variable)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *variable;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_char_mutex(pthread_mutex_t *mutex, char *to_change, char value)
{
	pthread_mutex_lock(mutex);
	*to_change = value;
	pthread_mutex_unlock(mutex);
}

char	get_char_mutex(pthread_mutex_t *mutex, char *variable)
{
	char	value;

	pthread_mutex_lock(mutex);
	value = *variable;
	pthread_mutex_unlock(mutex);
	return (value);
}
