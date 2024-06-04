/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maggie <maggie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/04 12:04:17 by maggie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_simulation(t_philo *philo){
	while(!get_char_mutex(philo->base->general_mutex, philo->base->simulation_ready));
}

void	dinner(t_all *base){
	int	i;
	
	if (base->min_meals == 0)
		return ; 
	i = -1;
	while(++i < base->n_philo)
		pthread_create(base->philo[i]->philo_thread, NULL, philo_simulation, base->philo[i]);
	base->start_time = get_time(MILLISECONDS);
	set_char_mutex(base->general_mutex, &(base->simulation_ready), 1);
	i = -1;
	while(++i < base->philo)
		pthread_join(base->philo[i]->philo_thread, NULL);

	// We reach this point when all philosophers are full!
}
