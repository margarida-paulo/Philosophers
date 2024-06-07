/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/07 12:40:08 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork->lock_mtx);
	display_message(philo, TAKE_FIRST_FORK);
	pthread_mutex_lock(philo->second_fork->lock_mtx);
	display_message(philo, TAKE_SECOND_FORK);
	philo->last_meal_time = get_time(MILLISECONDS);
	philo->meals_eaten++;
	display_message(philo, EATING);
	my_own_usleep(philo->base->time_to_die, philo->base);
	if (philo->base->limit_of_meals == philo->meals_eaten)
		philo->full = 1;
	pthread_mutex_unlock(philo->first_fork->lock_mtx);
	pthread_mutex_unlock(philo->second_fork->lock_mtx);
}

void	display_message(t_philo *philo, t_actions action)
{
	long time_since_start;

	if (philo->full)
		return ;
	time_since_start = get_time(MILLISECONDS) - philo->base->start_time;
	pthread_mutex_lock(philo->base->write_mtx);
	if ((action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK) && \
	!sim_finished(philo->base))
		printf(MAGENTA"%-6ld"RESET"%d has taken a fork.\n", \
		time_since_start, philo->id);
	if (action == EATING && !sim_finished(philo->base))
		printf(MAGENTA"%-6ld"RESET"%d is eating.\n", \
		time_since_start, philo->id);
	if (action == THINKING && !sim_finished(philo->base))
		printf(MAGENTA"%-6ld"RESET"%d is thinking.\n", \
		time_since_start, philo->id);
	if (action == SLEEPING && !sim_finished(philo->base))
		printf(MAGENTA"%-6ld"RESET"%d is sleeping.\n", \
		time_since_start, philo->id);
	if (action == DIED && !sim_finished(philo->base))
		printf(MAGENTA"%-6ld"RESET"%d died.\n", \
		time_since_start, philo->id);
	pthread_mutex_unlock(philo->base->write_mtx);
}

void	*philo_simulation(void *philosopher)
{
	t_philo *philo = (t_philo *)philosopher;
	while(!get_char_mutex(philo->base->sim_finished_mtx, philo->base->simulation_ready));

	while(!sim_finished(philo->base))
	{
		// Is it full?

		// Eat

		// Sleep
		display_message(philo, SLEEPING);
		my_own_usleep(philo->base->time_to_sleep, philo->base);

		// Think
	}
	return (NULL);
}

int	dinner(t_all *base){
	int	i;

	if (base->limit_of_meals == 0)
		return 0;
	i = -1;
	if (pthread_mutex_init(base->sim_finished_mtx, NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	while(++i < base->n_philo)
		pthread_create(base->philo[i]->philo_thread, NULL, philo_simulation, base->philo[i]);
	base->start_time = get_time(MILLISECONDS);
	set_char_mutex(base->sim_finished_mtx, &(base->simulation_ready), 1);
	i = 0;
	while(i < base->philo[i]->id)
	{
		pthread_join(*(base->philo[i]->philo_thread), NULL);
		i++;
	}
	return (0);

	// We reach this point when all philosophers are full!
}

char	sim_finished(t_all *base)
{
	return get_char_mutex(base->sim_finished_mtx, base->simulation_finished);
}
