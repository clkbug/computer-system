#include "csapp.h"

int counter = 1;

int
main()
{
    if (Fork() == 0) {
        counter--;
        exit(0);
    } else {
        Wait(NULL);
        printf("counter = %d\n", ++counter); // 2
    }
    return 0;
}