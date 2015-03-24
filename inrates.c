#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    long long ints[1001];
    int i;
    struct timespec z;
    char *buffer;
    
    buffer = malloc(1024*1024);
    if (buffer == NULL) return -1;
    
    for (i=0;i<1001;i++) ints[i]=0;
    
    if (clock_gettime(CLOCK_REALTIME, &z)) return -2;
    i = z.tv_nsec;
    
    while(fread(buffer, 1, 1024*32, stdin)) {
        if (clock_gettime(CLOCK_REALTIME, &z)) return -2;
	i = z.tv_nsec - i;
	while (i<0) i += 1000000000;
	while (i>=1000000000) i -= 1000000000;
	i /= 1000000;
	ints[i]++;
	i = z.tv_nsec;
    }
    for (i=0;i<1001;i++) if (ints[i]) printf("%u %llu\n", i+1, ints[i]);

    free(buffer);
    
    return 0;
}

