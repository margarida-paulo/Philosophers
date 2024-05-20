/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:59 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/20 12:17:49 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//Arguments: number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | [number_of_times_each_philosopher_must_eat]

int main(int argc, char **argv)
{
	t_all base;
	if (parse_input(&base, argc, argv))
		return (EXIT_FAILURE);
	free_forks_until(&base, base.n_philo - 1);
	free_philo_until(&base, base.n_philo - 1);
	free(base.philo);
	free(base.forks);
}
