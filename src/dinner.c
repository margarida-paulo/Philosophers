/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/17 19:26:36 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	if (get_char_mutex(&(philo->base->someone_died_mtx), philo->base->someone_died))
		return;
	pthread_mutex_lock(&(philo->first_fork->lock_mtx));
	display_message(philo, TAKE_FIRST_FORK);
	pthread_mutex_lock(&(philo->second_fork->lock_mtx));
	display_message(philo, TAKE_SECOND_FORK);
	philo->last_meal_time = get_time(MILLISECONDS);
	philo->meals_eaten++;
	display_message(philo, EATING);
	my_own_usleep(philo->base->time_to_die, philo->base);
	if (philo->base->limit_of_meals == philo->meals_eaten)
		philo->full = 1;
	pthread_mutex_unlock(&(philo->first_fork->lock_mtx));
	pthread_mutex_unlock(&(philo->second_fork->lock_mtx));
}

void	display_message(t_philo *philo, t_actions action)
{
	long time_since_start;

	if (philo->full)
		return ;
	time_since_start = get_time(MILLISECONDS) - philo->base->start_time;
	pthread_mutex_lock(&(philo->base->write_mtx));
	if ((action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK) && \
	!sim_finished(philo->base))
		printf("%-6ld%d has taken a fork.\n", \
		time_since_start, philo->id + 1);
	if (action == EATING && !sim_finished(philo->base))
		printf("%-6ld%d is eating.\n", \
		time_since_start, philo->id + 1);
	if (action == THINKING && !sim_finished(philo->base))
		printf("%-6ld%d is thinking.\n", \
		time_since_start, philo->id + 1);
	if (action == SLEEPING && !sim_finished(philo->base))
		printf("%-6ld%d is sleeping.\n", \
		time_since_start, philo->id + 1);
	if (action == DIED && !sim_finished(philo->base))
		printf("%-6ld%d died.\n", \
		time_since_start, philo->id + 1);
	pthread_mutex_unlock(&(philo->base->write_mtx));
}

void	*philo_simulation(void *philosopher)
{
	t_philo *philo;
	philo = (t_philo *)philosopher;
	while(!get_char_mutex(&(philo->base->sim_finished_mtx), philo->base->simulation_ready))
		usleep(1);
	philo->last_meal_time = philo->base->start_time;
	while(!sim_finished(philo->base) && !get_char_mutex(&(philo->full_mtx), philo->full))
	{
		if (get_char_mutex(&(philo->base->someone_died_mtx), philo->base->someone_died))
			return (NULL);
		// Is it full?
		if (get_char_mutex(&(philo->full_mtx), philo->full))
			return (NULL);

		// Eat
		eat(philo);
		if (philo->meals_eaten == philo->base->limit_of_meals)
			philo->full = 1;
		if (get_char_mutex(&(philo->base->someone_died_mtx), philo->base->someone_died))
			return (NULL);

		// Sleep
		display_message(philo, SLEEPING);
		my_own_usleep(philo->base->time_to_sleep, philo->base);
		if (get_char_mutex(&(philo->base->someone_died_mtx), philo->base->someone_died))
			return (NULL);
		// Think
	}
	return (NULL);
}

void	*check_for_deaths(void *base_void)
{
	t_all 	*base;
	int		i;

	base = (t_all *)base_void;
	while (!base->someone_died)
	{
		i = 0;
		while (i < base->n_philo && !base->someone_died)
		{
			if (get_char_mutex(&(base->philo[i]->full_mtx), !(base->philo[i]->full)))
			{
				if (get_time(MILLISECONDS) - base->philo[i]->last_meal_time > base->time_to_die)
					set_char_mutex(&(base->philo[i]->death_mtx), &(base->philo[i]->is_dead), 1);
				display_message(base->philo[i], DIED);
				base->someone_died = 1;
			}

		}
	}
	return (NULL);
}

int	dinner(t_all *base){
	int	i;

	if (base->limit_of_meals == 0)
		return 0;
	i = -1;
	if (pthread_mutex_init(&(base->sim_finished_mtx), NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	if (pthread_mutex_init(&(base->someone_died_mtx), NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		pthread_mutex_destroy(&(base->someone_died_mtx));
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	while(++i < base->n_philo)
	{
		pthread_create(&(base->philo[i]->philo_thread), NULL, philo_simulation, base->philo[i]);
		if (pthread_mutex_init(&(base->philo[i]->death_mtx), NULL))
		{
			pthread_mutex_destroy(&(base->sim_finished_mtx));
			pthread_mutex_destroy(&(base->someone_died_mtx));
			destroy_fork_mutexes_until(base, base->n_philo - 1);
			destroy_death_mutexes_until(base, i - 1);
			free_everything(base);
			return (exit_error("General mutex init failed!"));
		}
		if (pthread_mutex_init(&(base->philo[i]->full_mtx), NULL))
		{
			pthread_mutex_destroy(&(base->sim_finished_mtx));
			pthread_mutex_destroy(&(base->someone_died_mtx));
			destroy_fork_mutexes_until(base, base->n_philo - 1);
			destroy_death_mutexes_until(base, i);
			destroy_full_mutexes_until(base, i - 1);
			free_everything(base);
			return (exit_error("General mutex init failed!"));
		}
	}
	base->start_time = get_time(MILLISECONDS);
	set_char_mutex(&(base->sim_finished_mtx), &(base->simulation_ready), 1);
	pthread_create((&(base->death_checker)), NULL, check_for_deaths, base);
	i = 0;
	while(i < base->n_philo)
	{
		pthread_join(base->philo[i]->philo_thread, NULL);
		i++;
	}
	pthread_join(base->death_checker, NULL);
	return (0);

	// We reach this point when all philosophers are full!
}

char	sim_finished(t_all *base)
{
	return get_char_mutex(&(base->sim_finished_mtx), base->simulation_finished);
}
