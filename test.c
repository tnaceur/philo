#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
    struct timeval t;
    gettimeofday(&t, 0);
    printf("%ld : %d\n", t.tv_sec, t.tv_usec); 
}