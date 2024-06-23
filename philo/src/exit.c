/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:47 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 16:08:57 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* Prints the error message sent to it in the color read and
returns EXIT_FAILURE.
*/
int	exit_error(char *str_error)
{
	printf(RED "%s" RESET "\n", str_error);
	return (EXIT_FAILURE);
}

/* Frees the philosophers in the array until the index i sent as an argument.*/
void	free_philo_until(t_all *base, int i)
{
	int	a;

	a = -1;
	while (++a <= i)
		free((base->philo)[a]);
}

/* Frees the forks in the array until the index i sent as an argument.*/
void	free_forks_until(t_all *base, int i)
{
	int	a;

	a = -1;
	while (++a <= i)
		free((base->forks)[a]);
}
