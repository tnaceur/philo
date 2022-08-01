

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// milliseconds

long long ft_time(long long time)
{
    struct timeval hello;
    gettimeofday(&hello, 0);
    return ((hello.tv_sec * 1000) + (hello.tv_usec / 1000) - time);
}

int main()
{
    long long time = ft_time(0);
    while (1)
    {
        usleep(100000);
        printf("%lld\n", ft_time(time));
    }
}

