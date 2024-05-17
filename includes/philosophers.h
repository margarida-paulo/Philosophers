#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

typedef struct s_philosopers t_philo;
typedef struct s_forks t_forks;
typedef struct s_everything t_all;

// Exit
void	exit_error(char *str_error);

// Utils
// 1
size_t	ft_chars(long int a);
char	*ft_itoa(int n);
size_t	ft_strlen(char *s);
char ft_check_int(char *number);
int	ft_atoi_ph(char *nptr);

// 2
int	ft_strcmp(char *str1, char *str2);
char	ft_atoi_check(char *nptr);


// Parse input
void	validate_input(int argc, char **argv);
void	parse_input(int argc, char **argv);


// ********** Structs **********

struct s_philosophers
{
	long			id;
	long			meals_eaten;
	char			limit_of_meals;
	long			last_meal_time;
	pthread_t 		philo;
	t_forks			*left_fork;
	t_forks			*right_fork;
};

struct s_forks
{
	pthread_mutex_t lock;
	unsigned int	id;
};

struct s_everything
{
	t_forks	*forks;
	t_philo	*philo;
};
