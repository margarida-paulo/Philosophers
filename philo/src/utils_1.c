/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:55:08 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/23 20:11:16 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	ft_chars(long int a)
{
	size_t	divisors;
	size_t	chars;

	chars = 1;
	if (a < 0)
	{
		chars++;
		a = -a;
	}
	if (a == 0)
		return (1);
	divisors = 10;
	while (a / divisors != 0)
	{
		divisors = divisors * 10;
		chars = chars + 1;
	}
	return (chars);
}

char	*ft_itoa(int n)
{
	char			*string;
	size_t			i;
	unsigned int	number;

	string = (char *) malloc(sizeof(char) * (ft_chars((long int)n) + 1));
	if (!string)
		return (NULL);
	if (n < 0)
		number = -n;
	else
		number = n;
	i = ft_chars(n) - 1;
	string[i + 1] = '\0';
	while (i > 0)
	{
		string[i] = '0' + (number % 10);
		number = number / 10;
		i--;
	}
	if (n < 0)
		string[0] = '-';
	else
		string[0] = '0' + (number % 10);
	return (string);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
Returns 2 if the argument overflows int, 0 if it doesn't,
and 3 if there are non-numeric values.
*/
char	ft_check_int(char *number)
{
	int		i;
	char	*int_max;

	i = 0;
	if (!number || !number[i])
		return (3);
	while (number && number[i])
	{
		if (!(number[i] >= '0' && number[i] <= '9'))
			return (3);
		i++;
	}
	i = 0;
	int_max = ft_itoa(INT_MAX);
	if (ft_strlen(int_max) < ft_strlen(number) || \
	(ft_strlen(int_max) == ft_strlen(number) && ft_strcmp(int_max, number) > 0))
	{
		free(int_max);
		return (2);
	}
	free(int_max);
	return (0);
}

/*
Converts a string into an int. Is performed after the program
already checked it is a valid, positive number.
*/
int	ft_atoi_ph(char *nptr)
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
		exit_error("Negative arguments not accepted!");
	else if (nptr[i] == '+')
	{
		a = 1;
		i++;
	}
	while (nptr[i] == '0')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (res * a);
}
