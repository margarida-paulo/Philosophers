/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:37:51 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/17 11:14:20 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//t_all	*create_base_structs()
//{
//	t_all	*base;
//	base = malloc(sizeof(t_all*));
//	if (!base)
//		exit_error("Malloc of base structure failed");
//	base->forks = malloc(sizeof(t_forks*) * )
//}

void	validate_input(int argc, char **argv)
{
	int	i;
	int atoi;

	i = 1;
	if (argc != 5 && argc != 6)
		exit_error("Invalid number of arguments!");
	while (argv[i])
	{
		if (!(argv[i]))
			exit_error("Null argument!");
		atoi = ft_atoi_check(argv[i]);
		if (atoi == 1)
			exit_error("Negative arguments are not valid!");
		else if (atoi == 2)
			exit_error("Argument overflows int!");
		else if (atoi == 3)
			exit_error("Argument has non-numeric values!");
		i++;
	}
}

void	parse_input(int argc, char **argv)
{
	validate_input(argc, argv);
//	create_base_structs;
}

