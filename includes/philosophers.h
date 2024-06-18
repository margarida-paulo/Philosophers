/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maggie <maggie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:34:19 by mvalerio          #+#    #+#             */
/*   Updated: 2024/06/18 10:26:08 by maggie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Arguments: number_of_philosophers | time_to_die | time_to_eat | time_to_sleep | [min_meals]

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

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

# define SECONDS 0
# define MILLISECONDS 1
# define USECS 2

#define DEBUG	1

typedef struct s_philosophers	t_philo;
typedef struct s_forks	t_forks;
typedef struct s_everything	t_all;

typedef enum s_philo_actions
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
} t_actions;


// Exit
int		exit_error(char *str_error);
void	free_philo_until(t_all *base, int i);
void	free_forks_until(t_all *base, int i);
void	destroy_fork_mutexes_until(t_all *base, int i);
void	free_everything(t_all *base);
void	final_free_destroy(t_all *base);
void	destroy_full_mutexes_until(t_all *base, int i);

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
int	init_mutexes(t_all *base, int i);

// Dinner
void	eat(t_philo *philo);
void	display_message(t_philo *philo, t_actions action);
void	*philo_simulation(void *philosopher);
int		dinner(t_all *base);
char	sim_finished(t_all *base);



// Get Set
void	set_char_mutex(pthread_mutex_t *mutex, char *to_change, char value);
char	get_char_mutex(pthread_mutex_t *mutex, char variable);
void	set_long_mutex(pthread_mutex_t *mutex, long *to_change, long value);
long	get_long_mutex(pthread_mutex_t *mutex, long variable);
long	get_time(char time_type);
void	my_own_usleep(long time_usec, t_all *base);

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
	int				id;
	char			full;
	long			meals_eaten;
	long			last_meal_time;
	pthread_t 		philo_thread;
	t_forks			*first_fork;
	t_forks			*second_fork;
	t_all			*base;
	char			is_dead;
	pthread_mutex_t	philo_mtx;
};

// Id -> Id of the fork, starts at 0
// Lock -> Mutex of the fork to make sure only one philosopher
//grabs it at a time
struct s_forks
{
	pthread_mutex_t lock_mtx;
	unsigned int	id;
};


struct s_everything
{
	t_forks			**forks;
	t_philo			**philo;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				limit_of_meals;
	char			simulation_ready;
	pthread_mutex_t sim_finished_mtx;
	pthread_mutex_t write_mtx;
	long			start_time;
	char			simulation_finished;
	pthread_t		death_checker;
	};
