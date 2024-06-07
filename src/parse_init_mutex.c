/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maggie <maggie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:29:09 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/04 17:20:21 by maggie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutexes(t_all *base, int i)
{
	while (++i < base->n_philo)
	{
		if (pthread_mutex_init(&((base->forks)[i])->lock, NULL))
		{
			destroy_fork_mutexes_until(base, i);
			free_everything(base);
			return(exit_error("Forks init failed."));
		}
		((base->forks)[i])->id = i;
	}
	if (pthread_mutex_init(base->general_mutex, NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	if (pthread_mutex_init(base->write_mutex, NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	return (0);
}
