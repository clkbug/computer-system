#include "csapp.h"

int counter = 0;

void
handler(int sig)
{
    counter++;
    sleep(1);
    return;
}

int
main()
{
    Signal(SIGUSR2, handler);

    if (Fork() == 0) {
        for (int i = 0; i < 5; i++) {
            Kill(getppid(), SIGUSR2);
            printf("sent SIGUSR2 to parent\n");
            sleep(2); // シグナルは同時に1つしか保持できないので sleep すればOK
        }
        exit(0);
    }

    Wait(NULL);
    printf("counter=%d\n", counter);
    exit(0);
}