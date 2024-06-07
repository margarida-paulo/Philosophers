/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maggie <maggie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/04 17:22:49 by maggie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* Prints the error message sent to it in the color read and 
returns EXIT_FAILURE.
*/
int	exit_error(char *str_error)
{
	printf(RED "%s" RESET "\n", str_error);
	return(EXIT_FAILURE);
}

/* Frees the philosophers in the array until the index i sent as an argument.*/
void	free_philo_until(t_all *base, int i)
{
	int	a;

	a = -1;
	while (++a <= i)
		free((base->philo)[a]);
}

/* Frees the forks in the array until the index i sent as an argument.*/
void	free_forks_until(t_all *base, int i)
{
	int	a;

	a = -1;
	while (++a <= i)
		free((base->forks)[a]);
}

/* Destroys the mutexes of the forks until the index i sent as an argument.*/
void	destroy_fork_mutexes_until(t_all *base, int i)
{
	while (i >= 0)
		pthread_mutex_destroy(&((base->forks)[i]->lock));
}

/* Frees the array of forks and the array of philosophers.*/
void	free_everything(t_all *base)
{
	free_forks_until(base, base->n_philo - 1);
	free_philo_until(base, base->n_philo - 1);
	free(base->philo);
	free(base->forks);
}

void	final_free_destroy(t_all *base)
{
	pthread_mutex_destroy(base->general_mutex);
	pthread_mutex_destroy(base->write_mutex);
	free_everything(base);
}
