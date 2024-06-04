/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maggie <maggie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:59 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/31 09:56:22 by maggie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//Arguments: number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | [number_of_times_each_philosopher_must_eat]

int main(int argc, char **argv)
{
	t_all base;
	if (parse_init(&base, argc, argv))
		return (EXIT_FAILURE);
	dinner(&base);
	free_everything(&base);
}
