/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:24:35 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 16:05:46 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 && !str2)
		return (0);
	else if (!str1)
		return ((int)-(str2[0]));
	else if (!str2)
		return ((int)str1[0]);
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/*
Returns 0 if everything went correctly,
1 if the argument is negative, 2 if the argument overflows int, and
3 if the argument has non-numeric values.
*/
char	ft_atoi_check(char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		return (1);
	else if (nptr[i] == '+')
	{
		i++;
	}
	while (nptr[i] == '0')
		i++;
	return (ft_check_int(&(nptr[i])));
}

void	ft_print_philos(t_all *base)
{
	int	i;

	i = 0;
	while (i < base->n_philo)
	{
		printf("Philo ID:%d\n", base->philo[i]->id);
		printf("Philo First Fork:%d\n", base->philo[i]->first_fork->id);
		printf("Philo Second Fork:%d\n\n", base->philo[i]->second_fork->id);
		i++;
	}
}

void	all_philos_active(t_all *base)
{
	while (get_int_mutex(&(base->write_mtx), \
	&(base->active_philos)) != base->n_philo)
		usleep(50);
}

char	sim_finished(t_all *base)
{
	return (get_char_mutex(&(base->sim_finished_mtx), \
	&(base->simulation_finished)));
}
