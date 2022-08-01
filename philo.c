#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct trhead {

	pthread_t		*t;
	pthread_mutex_t	lock;
	struct timeval 	start;
	time_t			end;
	int				j;
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
	usleep(100000);
	printf("The philo number : %d\n", thread->j);
	pthread_mutex_unlock(&thread->lock);
	return (NULL);
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		while (1)
		{
			s_thread	t;
			int			i;
			int			start;

			t.j = 0;
			i = 0;
			t.t = malloc(sizeof(s_thread) * ft_atoi(av[1]));
			pthread_mutex_init(&t.lock, NULL);
			t.end = ft_atoi(av[2]);
			gettimeofday(&t.start, NULL);
			start = t.start.tv_usec;
			while (i < ft_atoi(av[1]))
			{
				// if (t.start.tv_usec >= start + t.end)
				// 	return (0);
				pthread_create(&t.t[i], NULL, &fct, &t);
				i++;
			}
			i = 0;
			while (i < ft_atoi(av[1]))
				pthread_join(t.t[i++], NULL);
	}	}
}
