#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct trhead {

	pthread_t	*t;
	pthread_mutex_t	lock;
	int	j;
} s_thread;

int	ft_atoi(char *s)
{
	int	i;
	int	num;
	int	signe;

	i = 0;
	signe = 1;
	num = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signe = -1;
		i++;
	}
	if (s[i] == '-' || s[i] == '+')
		exit(printf("Error\n"));
	while (s[i])
	{
		num *= 10;
		num += s[i] - '0';
		i++;
	}
	return (num * signe);

}

void*	fct(void *x)
{
	s_thread *thread = (s_thread*)x;
	pthread_mutex_lock(&thread->lock);
	thread->j++;
	sleep(1);
	printf("The philo number : %d\n", thread->j);
	pthread_mutex_unlock(&thread->lock);
	return (0);
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		s_thread	x;
		int			i;

		x.j = 0;
		i = 0;
		x.t = malloc(sizeof(s_thread) * ft_atoi(av[1]));
		pthread_mutex_init(&x.lock, NULL);
		while (i < ft_atoi(av[1]))
		{
			pthread_create(&x.t[i], NULL, &fct, &x);
			usleep(100);
			i++;
		}
		i = 0;
		while (i < ft_atoi(av[1]))
		{
			pthread_join(x.t[i], NULL);
			i++;
		}
	}
}
