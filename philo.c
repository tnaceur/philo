#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct trhead {

	pthread_t		*t;
	pthread_mutex_t	*lock;
	struct timeval 	start;
	time_t			end;
	int				id;
	int				time_to_eat;
	int	 		 	time_to_die;
	int		 		time_to_sleep;
	int	 	 	 	num_of_eat;
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
	pthread_mutex_lock(&thread->lock[thread->id]);
	printf("thread %d take the left fork\n", thread->id + 1);
	pthread_mutex_lock(&thread->lock[++thread->id]);
	printf("thread %d take the right fork\n", thread->id);
	// usleep(19999);
	pthread_mutex_unlock(&thread->lock[--thread->id]);
	pthread_mutex_unlock(&thread->lock[++thread->id]);
	// printf("philo %d take the right fork\n", thread->id);
	// thread->id++;
	// pthread_mutex_lock(&thread->lock[(thread->id + 1) % total_philo]);
	// printf("philo %d take the left fork\n", thread->id);
	// usleep(10000);
	// printf("The philo number : %d\n", thread->id);
	// pthread_mutex_unlock(&thread->lock[thread->id]);
	return (NULL);
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		while (1)
		{
			int			start;
			s_thread	t;
			int			i;

			// t.id = 0;
			i = 0;
			t.t = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
			t.lock = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
			while (i < ft_atoi(av[1]))
			{
				pthread_mutex_init(&t.lock[i], NULL);
				i++;
			}
			i = 0;
			while (i < ft_atoi(av[1]))
			{
				t.id = i;
				pthread_create(&t.t[i], NULL, &fct, &t);
				i++;
				usleep(199099);
			}
			i = 0;
			// while (i < ft_atoi(av[1]))
			// 	pthread_join(t.t[i++], NULL);
	}	}
}
