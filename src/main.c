/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:59 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 15:58:42 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//Arguments: number_of_philosophers | time_to_die |
//time_to_eat | time_to_sleep | [number_of_times_each_philosopher_must_eat]

int	main(int argc, char **argv)
{
	t_all	*base;

	base = malloc(sizeof(t_all));
	if (!base)
		return (exit_error("Malloc of main struct failed.\n"));
	if (parse_init(base, argc, argv))
		return (EXIT_FAILURE);
	dinner(base);
	final_free_destroy(base);
}
