/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 13:34:29 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	if (sim_finished(philo->base))
		return ;
	pthread_mutex_lock(&(philo->first_fork->lock_mtx));
	if (sim_finished(philo->base))
	{
		pthread_mutex_unlock(&(philo->first_fork->lock_mtx));
		return ;
	}
	display_message(philo, TAKE_FIRST_FORK);
	pthread_mutex_lock(&(philo->second_fork->lock_mtx));
	if (sim_finished(philo->base))
	{
		pthread_mutex_unlock(&(philo->first_fork->lock_mtx));
		pthread_mutex_unlock(&(philo->second_fork->lock_mtx));
		return ;
	}
	display_message(philo, TAKE_SECOND_FORK);
	set_long_mutex(&(philo->philo_mtx), &(philo->last_meal_time), get_time(MILLISECONDS));
	display_message(philo, EATING);
	my_own_usleep(philo->base->time_to_eat, philo->base);
	philo->meals_eaten++;
	if (philo->base->limit_of_meals == philo->meals_eaten)
		philo->full = 1;
	pthread_mutex_unlock(&(philo->first_fork->lock_mtx));
	pthread_mutex_unlock(&(philo->second_fork->lock_mtx));
}

static void think(t_philo *philo)
{
	if (philo->base->time_to_think != 0)
		my_own_usleep(philo->base->time_to_sleep, philo->base);
	display_message(philo, THINKING);
}

void	display_message(t_philo *philo, t_actions action)
{
	long time_since_start;

	if (philo->full)
		return ;
	pthread_mutex_lock(&(philo->base->write_mtx));
	time_since_start = get_time(MILLISECONDS) - philo->base->start_time;
		if ((action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK) && \
		!sim_finished(philo->base))
			printf("%-6ld%d has taken a fork\n", \
			time_since_start, philo->id + 1);
		if (action == EATING && !sim_finished(philo->base))
			printf("%-6ld%d is eating\n", \
			time_since_start, philo->id + 1);
		if (action == THINKING && !sim_finished(philo->base))
			printf("%-6ld%d is thinking\n", \
			time_since_start, philo->id + 1);
		if (action == SLEEPING && !sim_finished(philo->base))
			printf("%-6ld%d is sleeping\n", \
			time_since_start, philo->id + 1);
		if (action == DIED)
			printf("%-6ld%d died\n", \
			time_since_start, philo->id + 1);
		pthread_mutex_unlock(&(philo->base->write_mtx));
}

void	*philo_simulation(void *philosopher)
{
	t_philo *philo;
	philo = (t_philo *)philosopher;

	while(!get_char_mutex(&(philo->base->sim_finished_mtx), &(philo->base->simulation_ready)))
		usleep(50);
	set_long_mutex(&(philo->philo_mtx), &(philo->last_meal_time), philo->base->start_time);
	pthread_mutex_lock(&(philo->base->write_mtx));
	philo->base->active_philos++;
	pthread_mutex_unlock(&(philo->base->write_mtx));
	while(!sim_finished(philo->base) && !get_char_mutex(&(philo->philo_mtx), &(philo->full)))
	{
		// Is it full?
		if (sim_finished(philo->base))
			return (NULL);

		// Eat
		eat(philo);
		if (philo->meals_eaten == philo->base->limit_of_meals)
			philo->full = 1;
		if (get_char_mutex(&(philo->philo_mtx), &(philo->full)) || sim_finished(philo->base))
			return (NULL);

		// Sleep
		display_message(philo, SLEEPING);
		my_own_usleep(philo->base->time_to_sleep, philo->base);
		// Think
		if (get_char_mutex(&(philo->philo_mtx), &(philo->full)) || sim_finished(philo->base))
			return (NULL);

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
	while (get_int_mutex(&(base->write_mtx), &(base->active_philos)) != base->n_philo)
		usleep(50);
	while (!sim_finished(base))
	{
		i = 0;
		while(i < base->n_philo && !sim_finished(base))
		{
			time_diff = get_time(MILLISECONDS) - \
			get_long_mutex(&(base->philo[i]->philo_mtx), &(base->philo[i]->last_meal_time));
			if (time_diff * 1000 > base->time_to_die && \
			!get_char_mutex(&(base->philo[i]->philo_mtx), &(base->philo[i]->full)))
			{
				set_char_mutex(&(base->sim_finished_mtx), &(base->simulation_finished), 1);
				display_message(base->philo[i], DIED);
			}
			i++;
		}
	}
	return (NULL);
}
void	one_philo(t_all *base)
{
	long curr_time;

	base->start_time = get_time(MILLISECONDS);
	display_message(base->philo[0], TAKE_FIRST_FORK);
	curr_time = get_time(MILLISECONDS);
	while ((base->time_to_die > (curr_time - base->start_time) * 1000))
	{
		usleep(50);
		curr_time = get_time(MILLISECONDS);
	}
	display_message(base->philo[0], DIED);
	return ;
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
	else while(++i < base->n_philo)
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
	set_char_mutex(&(base->sim_finished_mtx), &(base->simulation_finished), 1);
	pthread_join(base->death_checker, NULL);
	return (0);
}

char	sim_finished(t_all *base)
{
	return get_char_mutex(&(base->sim_finished_mtx), &(base->simulation_finished));
}
