
#include "philo.h"

int	get_time_millisec()
{
	struct timeval	time;
	int				millisec;

	if (gettimeofday(&time, NULL) == FAILURE)
	{
		perror("gettimeofday");
		return (FAILURE);
	}
	millisec = (int) time.tv_sec * 1000 + (int) time.tv_usec / 1000;
	return (millisec);
}

void	set_value(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

bool	print_message(t_philo philo, char *msg)
{
	int	time;
	int	cur_time;

	if (philo.args->finish)
		return (false);
	cur_time = get_time_millisec();
	if (cur_time == FAILURE)
		return (false);
	time = cur_time - philo.args->start_time;
	pthread_mutex_lock(&philo.args->print);
	if (printf("%d %d %s", time, philo.index, msg) == FAILURE)
	{
		pthread_mutex_unlock(&philo.args->print);
		perror("printf");
		return (false);
	}
	pthread_mutex_unlock(&philo.args->print);
	return (true);
}
