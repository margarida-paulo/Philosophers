/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maggie <maggie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/18 14:20:20 by maggie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->first_fork->lock_mtx));
	display_message(philo, TAKE_FIRST_FORK);
	pthread_mutex_lock(&(philo->second_fork->lock_mtx));
	display_message(philo, TAKE_SECOND_FORK);
	set_long_mutex(&(philo->philo_mtx), &(philo->last_meal_time), get_time(MILLISECONDS));
	philo->meals_eaten++;
	display_message(philo, EATING);
	my_own_usleep(philo->base->time_to_eat, philo->base);
	if (philo->base->limit_of_meals == philo->meals_eaten)
		philo->full = 1;
	pthread_mutex_unlock(&(philo->first_fork->lock_mtx));
	pthread_mutex_unlock(&(philo->second_fork->lock_mtx));
}

static void think(t_philo *philo)
{
	display_message(philo, THINKING);
}

void	display_message(t_philo *philo, t_actions action)
{
	long time_since_start;

	if (philo->full)
		return ;
	pthread_mutex_lock(&(philo->base->write_mtx));
	time_since_start = get_time(MILLISECONDS) - philo->base->start_time;
	if (DEBUG)
	{
		if (action == TAKE_FIRST_FORK && !sim_finished(philo->base))
			printf("%-6ld%d has taken a fork.          |FORK: %d|\n", \
			time_since_start, philo->id + 1, philo->first_fork->id);
		if (action == TAKE_SECOND_FORK && !sim_finished(philo->base))
			printf("%-6ld%d has taken a fork.          |FORK: %d|\n", \
			time_since_start, philo->id + 1, philo->second_fork->id);
		if (action == EATING && !sim_finished(philo->base))
			printf("%-6ld%d is eating.                 |MEALS: %ld|\n", \
			time_since_start, philo->id + 1, philo->meals_eaten);
		if (action == THINKING && !sim_finished(philo->base))
			printf("%-6ld%d is thinking.\n", \
			time_since_start, philo->id + 1);
		if (action == SLEEPING && !sim_finished(philo->base))
			printf("%-6ld%d is sleeping.\n", \
			time_since_start, philo->id + 1);
		if (action == DIED && !sim_finished(philo->base))
			printf("%-6ld%d died.\n", \
			time_since_start, philo->id + 1);		
	}
	else
	{
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
	}

	pthread_mutex_unlock(&(philo->base->write_mtx));
}

void	*philo_simulation(void *philosopher)
{
	t_philo *philo;
	philo = (t_philo *)philosopher;
	while(!get_char_mutex(&(philo->base->sim_finished_mtx), philo->base->simulation_ready))
		usleep(1);
	pthread_mutex_lock(&(philo->base->write_mtx));
	philo->base->active_philos++;
	pthread_mutex_unlock(&(philo->base->write_mtx));
	set_long_mutex(&(philo->philo_mtx), &(philo->last_meal_time), philo->base->start_time);
	while(!sim_finished(philo->base) && !get_char_mutex(&(philo->philo_mtx), philo->full))
	{
		// Is it full?
		if (get_char_mutex(&(philo->philo_mtx), philo->full))
			return (NULL);

		// Eat
		eat(philo);
		if (philo->meals_eaten == philo->base->limit_of_meals)
			philo->full = 1;

		// Sleep
		display_message(philo, SLEEPING);
		my_own_usleep(philo->base->time_to_sleep, philo->base);
		// Think

		think(philo);
	}
	return (NULL);
}

void	*check_deaths(void *base_void)
{
	t_all	*base;
	int		i;
	long		time_diff;

	base = (t_all *)base_void;
	while (get_int_mutex(&(base->write_mtx), base->active_philos) != base->n_philo)
		usleep(1);
	while (!sim_finished(base))
	{
		i = 0;
		while(i < base->n_philo && !sim_finished(base))
		{
			time_diff = get_time(MILLISECONDS) - \
			get_long_mutex(&(base->philo[i]->philo_mtx), base->philo[i]->last_meal_time);
			pthread_mutex_lock(&(base->write_mtx));
			pthread_mutex_unlock(&(base->write_mtx));			
			if (time_diff * 1000 > base->time_to_die && \
			!get_char_mutex(&(base->philo[i]->philo_mtx), base->philo[i]->full))
			{
				display_message(base->philo[i], DIED);
				set_char_mutex(&(base->sim_finished_mtx), &(base->simulation_finished), 1);
			}
			i++;
		}
	}
	return (NULL);
}

void	one_philo(t_all *base)
{
	long start_time;
	long time;

	start_time = get_time(MILLISECONDS);
	printf("%-6ld%d has taken a fork.\n", \
	get_time(MILLISECONDS) - start_time, 1);
	usleep(base->time_to_die);
	time = get_time(MILLISECONDS) - start_time;
	printf("%-6ld%d died.\n", time, 1);		

}

int	dinner(t_all *base){
	int	i;
	if (base->limit_of_meals == 0)
		return (0);
	if (base->n_philo == 1)
	{
		one_philo(base);
		return (0);
	}
	i = -1;
	if (pthread_mutex_init(&(base->sim_finished_mtx), NULL))
	{
		destroy_fork_mutexes_until(base, base->n_philo - 1);
		free_everything(base);
		return (exit_error("General mutex init failed!"));
	}
	while(++i < base->n_philo)
	{
		pthread_create(&(base->philo[i]->philo_thread), NULL, philo_simulation, base->philo[i]);
		if (pthread_mutex_init(&(base->philo[i]->philo_mtx), NULL))
		{
			pthread_mutex_destroy(&(base->sim_finished_mtx));
			destroy_fork_mutexes_until(base, base->n_philo - 1);
			destroy_full_mutexes_until(base, i - 1);
			free_everything(base);
			return (exit_error("General mutex init failed!"));
		}
	}
	base->start_time = get_time(MILLISECONDS);
	set_char_mutex(&(base->sim_finished_mtx), &(base->simulation_ready), 1);
	pthread_create(&(base->death_checker), NULL, check_deaths, base);
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
