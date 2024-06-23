/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 16:09:12 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* Destroys the mutexes of the forks until the index i sent as an argument.*/
void	destroy_fork_mutexes_until(t_all *base, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&((base->forks)[i]->lock_mtx));
		i--;
	}
}

void	destroy_full_mutexes_until(t_all *base, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&((base->philo)[i]->philo_mtx));
		i--;
	}
}

/* Frees the array of forks and the array of philosophers.*/
void	free_everything(t_all *base)
{
	free_forks_until(base, base->n_philo - 1);
	free_philo_until(base, base->n_philo - 1);
	free(base->philo);
	free(base->forks);
	free(base);
}

void	final_free_destroy(t_all *base)
{
	pthread_mutex_destroy(&(base->sim_finished_mtx));
	pthread_mutex_destroy(&(base->write_mtx));
	free_everything(base);
}
