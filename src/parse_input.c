/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:51 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/20 12:10:26 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//Arguments: number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | [number_of_times_each_philosopher_must_eat]

int	init_philo_forks_structs(t_all *base, int i)
{
	while (++i < base->n_philo)
	{
		(base->philo)[i] = malloc(sizeof(t_philo));
		if (!base->philo[i])
		{
			free_philo_until(base, i - 1);
			free(base->forks);
			free(base->philo);
			return (exit_error("Malloc of one of the philosophers failed!"));
		}
		(base->forks)[i] = malloc(sizeof(t_forks));
		if (!base->philo[i])
		{
			free_philo_until(base, i);
			free_forks_until(base, i - 1);
			free(base->forks);
			free(base->philo);
			return (exit_error("Malloc of one of the forks failed!"));
		}
		(base->philo)[i]->id = 0;
		(base->philo)[i]->meals_eaten = 0;
	}
	return(0);
}

void	init_argv_to_base(t_all *base, char **argv, int argc)
{
	base->n_philo = ft_atoi_ph(argv[1]);
	base->time_to_die = ft_atoi_ph(argv[2]);
	base->time_to_eat = ft_atoi_ph(argv[3]);
	base->time_to_sleep = ft_atoi_ph(argv[4]);
	if(argc == 6)
		base->min_meals = ft_atoi_ph(argv[5]);
	else
		base->min_meals = -1;
}

int	init_base_struct(t_all *base, int argc, char **argv)
{
	base->n_philo = ft_atoi_ph(argv[1]);
	base->time_to_die = ft_atoi_ph(argv[2]);
	base->time_to_eat = ft_atoi_ph(argv[3]);
	base->time_to_sleep = ft_atoi_ph(argv[4]);
	if(argc == 6)
		base->min_meals = ft_atoi_ph(argv[5]);
	else
		base->min_meals = -1;
	base->forks = malloc(sizeof(t_forks*) * base->n_philo);
	if (!base->forks)
		return (exit_error("Malloc of forks failed!"));
	base->philo = malloc(sizeof(t_philo*) * base->n_philo);
	if (!base->philo)
	{
		free(base->forks);
		return (exit_error("Malloc of philosophers faled!"));
	}
	return(init_philo_forks_structs(base, -1));
}

int	invalid_input(int argc, char **argv)
{
	int	i;
	int atoi;

	i = 1;
	if (argc != 5 && argc != 6)
		return(exit_error("Invalid number of arguments!"));
	while (argv[i])
	{
		if (!(argv[i]))
			return(exit_error("Null argument!"));
		atoi = ft_atoi_check(argv[i]);
		if (atoi == 1)
			return(exit_error("Negative arguments are not valid!"));
		else if (atoi == 2)
			return(exit_error("Argument overflows int!"));
		else if (atoi == 3)
			return(exit_error("Argument has non-numeric values!"));
		i++;
	}
	return (0);
}

int	parse_input(t_all *base, int argc, char **argv)
{
	if (invalid_input(argc, argv))
		return(EXIT_FAILURE);
	if (init_base_struct(base, argc, argv))
		return(EXIT_FAILURE);
	return(0);
}

