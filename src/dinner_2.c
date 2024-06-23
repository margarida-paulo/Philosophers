/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 16:17:37 by mvalerio         ###   ########.fr       */
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
	set_long_mutex(&(philo->philo_mtx), &(philo->last_meal_time), get_time(MS));
	display_message(philo, EATING);
	my_own_usleep(philo->base->time_to_eat, philo->base);
	philo->meals_eaten++;
	if (philo->base->limit_of_meals == philo->meals_eaten)
		philo->full = 1;
	pthread_mutex_unlock(&(philo->first_fork->lock_mtx));
	pthread_mutex_unlock(&(philo->second_fork->lock_mtx));
}

void	think(t_philo *philo)
{
	display_message(philo, THINKING);
	if (philo->base->time_to_think > 0)
		my_own_usleep(philo->base->time_to_think * 0.42, philo->base);
}

void	display_message(t_philo *philo, t_actions action)
{
	long	time_since_start;

	if (philo->full)
		return ;
	pthread_mutex_lock(&(philo->base->write_mtx));
	time_since_start = get_time(MS) - philo->base->start_time;
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

void	unsync_philos(t_philo *philo)
{
	if (philo->base->n_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_own_usleep(3000, philo->base);
	}
	else
	{
		if (philo->id % 2)
			think(philo);
	}
}

void	*check_deaths(void *base_void)
{
	t_all	*base;
	int		i;
	long	time_diff;

	base = (t_all *)base_void;
	all_philos_active(base);
	while (!sim_finished(base))
	{
		i = -1;
		while (++i < base->n_philo && !sim_finished(base))
		{
			time_diff = get_time(MS) - \
			get_long_mutex(&(base->philo[i]->philo_mtx), \
			&(base->philo[i]->last_meal_time));
			if (time_diff * 1000 > base->time_to_die && \
			!get_char_mutex(&(base->philo[i]->philo_mtx), \
			&(base->philo[i]->full)))
			{
				set_char_mutex(&(base->sim_finished_mtx), \
				&(base->simulation_finished), 1);
				display_message(base->philo[i], DIED);
			}
		}
	}
	return (NULL);
}
