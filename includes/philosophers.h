/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvalerio <mvalerio@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:34:19 by mvalerio          #+#    #+#             */
/*   Updated: 2024/05/27 13:06:25 by mvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#define RESET		"\033[0m"
#define BLACK		"\033[30m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define BLUE		"\033[34m"
#define MAGENTA		"\033[35m"
#define CYAN		"\033[36m"
#define WHITE		"\033[37m"
#define BOLDBLACK	"\033[1m\033[30m"
#define BOLDRED		"\033[1m\033[31m"
#define BOLDGREEN	"\033[1m\033[32m"
#define BOLDYELLOW	"\033[1m\033[33m"
#define BOLDBLUE	"\033[1m\033[34m"
#define BOLDMAGENTA	"\033[1m\033[35m"
#define BOLDCYAN	"\033[1m\033[36m"
#define BOLDWHITE	"\033[1m\033[37m"

typedef struct s_philosophers	t_philo;
typedef struct s_forks	t_forks;
typedef struct s_everything	t_all;

// Exit
int		exit_error(char *str_error);
void	free_philo_until(t_all *base, int i);
void	free_forks_until(t_all *base, int i);
void	destroy_mutexes_until(t_all *base, int i);
void	free_everything(t_all *base);

// Utils
// 1
size_t	ft_chars(long int a);
char	*ft_itoa(int n);
size_t	ft_strlen(char *s);
char 	ft_check_int(char *number);
int		ft_atoi_ph(char *nptr);

// 2
int		ft_strcmp(char *str1, char *str2);
char	ft_atoi_check(char *nptr);
//Test Functions
void	ft_print_philos(t_all *base);


// Parse init
int		malloc_philo_forks_structs(t_all *base, int i);
void	init_argv_to_base(t_all *base, char **argv, int argc);
int		init_base_struct(t_all *base, int argc, char **argv);
int		invalid_input(int argc, char **argv);
int		parse_init(t_all *base, int argc, char **argv);

// Parse Input Mutexes
int	init_fork_mutexes(t_all *base);

// ********** Structs **********

/* NOTE: In reality, the philosophers have a left and a right fork,
but for the sake of deadlock protection, we assign a first and a
second fork. The first fork is the one that the philosophers are
gonna try to get first, and the second fork is the one that the
philosophers are gonna try to get second. Since odd philos
get the left fork as a first and even philos get the right fork
as a first, there is never gonna be a point where each person
has one fork and they are all staring into the void, waiting
for starvation to finally take the best of them.*/
struct s_philosophers
{
	int			id;
	int			full;
	long		meals_eaten;
	char		limit_of_meals;
	long		last_meal_time;
	pthread_t 	philo;
	t_forks		*first_fork;
	t_forks		*second_fork;
};

struct s_forks
{
	pthread_mutex_t lock;
	unsigned int	id;
};

struct s_everything
{
	t_forks	**forks;
	t_philo	**philo;
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_meals;
};
