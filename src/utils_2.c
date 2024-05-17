/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:24:35 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/17 11:03:19 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


int	ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	if (!str1 && !str2)
		return (0);
	else if (!str1)
		return (int)-(str2[0]);
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
	int	a;
	int	res;

	i = 0;
	a = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		return(1);
	else if (nptr[i] == '+')
	{
		a = 1;
		i++;
	}
	while(nptr[i] == '0')
		i++;
	return (ft_check_int(&(nptr[i])));
}


