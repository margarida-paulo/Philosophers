/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:29:09 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 15:59:42 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutexes(t_all *base, int i)
{
	while (++i < base->n_philo)
	{
		if (pthread_mutex_init(&(((base->forks)[i])->lock_mtx), NULL))
		{
			destroy_fork_mutexes_until(base, i);
			free_everything(base);
			return (exit_error("Forks init failed."));
		}
		((base->forks)[i])->id = i;
	}
	if (pthread_mutex_init(&(base->sim_finished_mtx), NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		free_everything(base);
		return (exit_error("Simulation finished mutex init failed!"));
	}
	if (pthread_mutex_init(&(base->write_mtx), NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		pthread_mutex_destroy(&(base->sim_finished_mtx));
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	return (0);
}
