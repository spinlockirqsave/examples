// if mmap fails, run first as root:
// echo 0 > /proc/sys/vm/mmap_min_addr

#include <stdio.h>
#include <sys/mman.h>


int main()
{
    int *p = NULL; // target
    if ( mmap( NULL, 4096, PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, -1, 0) == MAP_FAILED)
    {
        perror( "Mapping NULL failed");
        fprintf( stderr, "Is /proc/sys/vm/mmap_min_addr non-zero?");
        return -1;
    }

    printf( "Dereferencing now NULL yields:%d\n", *p);
    *p = 7;
    printf( "After writting to NULL, now *NULL=%d\n", *p);

    return 0;
}
