/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 16:06:54 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	start_basic_simulation(t_philo *philo)
{
	while (!get_char_mutex(&(philo->base->sim_finished_mtx), \
	&(philo->base->simulation_ready)))
		usleep(50);
	set_long_mutex(&(philo->philo_mtx), &(philo->last_meal_time), \
	philo->base->start_time);
	pthread_mutex_lock(&(philo->base->write_mtx));
	philo->base->active_philos++;
	pthread_mutex_unlock(&(philo->base->write_mtx));
	unsync_philos(philo);
}

void	*philo_simulation(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	start_basic_simulation(philo);
	while (!sim_finished(philo->base) && !get_char_mutex(&(philo->philo_mtx), \
	&(philo->full)))
	{
		if (sim_finished(philo->base))
			return (NULL);
		eat(philo);
		if (philo->meals_eaten == philo->base->limit_of_meals)
			philo->full = 1;
		if (get_char_mutex(&(philo->philo_mtx), &(philo->full)) || \
		sim_finished(philo->base))
			return (NULL);
		display_message(philo, SLEEPING);
		my_own_usleep(philo->base->time_to_sleep, philo->base);
		if (get_char_mutex(&(philo->philo_mtx), &(philo->full)) || \
		sim_finished(philo->base))
			return (NULL);
		think(philo);
	}
	return (NULL);
}

void	one_philo(t_all *base)
{
	long	curr_time;

	base->start_time = get_time(MS);
	display_message(base->philo[0], TAKE_FIRST_FORK);
	curr_time = get_time(MS);
	while ((base->time_to_die > (curr_time - base->start_time) * 1000))
	{
		usleep(50);
		curr_time = get_time(MS);
	}
	display_message(base->philo[0], DIED);
	return ;
}

void	simulation(t_all *base, int i)
{
	base->start_time = get_time(MS);
	set_char_mutex(&(base->sim_finished_mtx), &(base->simulation_ready), 1);
	pthread_create(&(base->death_checker), NULL, check_deaths, base);
	i = 0;
	while (i < base->n_philo)
	{
		pthread_join(base->philo[i]->philo_thread, NULL);
		i++;
	}
	set_char_mutex(&(base->sim_finished_mtx), &(base->simulation_finished), 1);
	pthread_join(base->death_checker, NULL);
}

int	dinner(t_all *base)
{
	int	i;

	if (base->limit_of_meals == 0)
		return (0);
	i = -1;
	if (base->n_philo == 1)
	{
		one_philo(base);
		return (0);
	}
	while (++i < base->n_philo)
	{
		pthread_create(&(base->philo[i]->philo_thread), NULL, \
		philo_simulation, base->philo[i]);
		if (pthread_mutex_init(&(base->philo[i]->philo_mtx), NULL))
		{
			pthread_mutex_destroy(&(base->sim_finished_mtx));
			destroy_fork_mutexes_until(base, base->n_philo - 1);
			destroy_full_mutexes_until(base, i - 1);
			free_everything(base);
			return (exit_error("General mutex init failed!"));
		}
	}
	simulation(base, i);
	return (0);
}
