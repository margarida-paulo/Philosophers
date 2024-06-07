/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maggie <maggie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/04 17:56:52 by maggie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	display_message(t_philo *philo, t_actions action)
{
	
	if ((action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK) && \
	!sim_finished(philo->base));
		printf("%d %.6ld %d Philosopher nº %d has taken a fork.\n", MAGENTA, \
		get_time(MILLISECONDS), RESET, philo->id);
	if (action == EATING && !sim_finished(philo->base));
		printf("%d %.6ld %d Philosopher nº %d is eating.\n", MAGENTA, \
		get_time(MILLISECONDS), RESET, philo->id);
	if (action == THINKING && !sim_finished(philo->base));
		printf("%d %.6ld %d Philosopher nº %d is thinking.\n", MAGENTA, \
		get_time(MILLISECONDS), RESET, philo->id);		
	if (action == SLEEPING && !sim_finished(philo->base));
		printf("%d %.6ld %d Philosopher nº %d is sleeping.\n", MAGENTA, \
		get_time(MILLISECONDS), RESET, philo->id);
	if (action == DIED && !sim_finished(philo->base));
		printf("%d %.6ld %d Philosopher nº %d died.\n", MAGENTA, \
		get_time(MILLISECONDS), RESET, philo->id);
}

void	philo_simulation(t_philo *philo)
{
	while(!get_char_mutex(philo->base->general_mutex, philo->base->simulation_ready));

	while(!sim_finished(philo->base))
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

char	sim_finished(t_all *base)
{
	return get_char_mutex(base->general_mutex, base->simulation_finished);
}