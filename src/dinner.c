/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/04 15:44:50 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_simulation(t_philo *philo){
	while(!get_char_mutex(philo->base->general_mutex, philo->base->simulation_ready));

	while(!(get_char_mutex(philo->base->general_mutex, philo->base->simulation_finished)))
	{
		// Is it full?

		// Eat

		// Sleep

		// Think
	}
}

void	dinner(t_all *base){
	int	i;

	if (base->min_meals == 0)
		return ;
	i = -1;
	if (pthread_mutex_init(base->general_mutex, NULL))
	{
		destroy_mutexes_until(base, base->n_philo - 1);
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	while(++i < base->n_philo)
		pthread_create(base->philo[i]->philo_thread, NULL, philo_simulation, base->philo[i]);
	base->start_time = get_time(MILLISECONDS);
	set_char_mutex(base->general_mutex, &(base->simulation_ready), 1);
	i = -1;
	while(++i < base->philo)
		pthread_join(base->philo[i]->philo_thread, NULL);

	// We reach this point when all philosophers are full!
}
