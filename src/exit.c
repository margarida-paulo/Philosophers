/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/27 11:14:29 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	exit_error(char *str_error)
{
	printf(RED "%s" RESET "\n", str_error);
	return(EXIT_FAILURE);
}

void	free_philo_until(t_all *base, int i)
{
	int	a;

	a = -1;
	while (++a <= i)
		free((base->philo)[a]);
}

void	free_forks_until(t_all *base, int i)
{
	int	a;

	a = -1;
	while (++a <= i)
		free((base->forks)[a]);
}

void	destroy_mutexes_until(t_all *base, int i)
{
	while (i >= 0)
		pthread_mutex_destroy(&((base->forks)[i]->lock));
}

void	free_everything(t_all *base)
{
	free_forks_until(base, base->n_philo - 1);
	free_philo_until(base, base->n_philo - 1);
	free(base->philo);
	free(base->forks);
}
