/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:29:09 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/27 11:37:24 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_fork_mutexes(t_all *base)
{
	int	i;

	i = 0;
	while (i < base->n_philo)
	{
		if (pthread_mutex_init(&((base->forks)[i])->lock, NULL))
		{
			destroy_mutexes_until(base, i);
			free_everything(base);
			return(exit_error("Forks init failed."));
		}
		((base->forks)[i])->id = i;
		i++;
	}
	return (0);
}
