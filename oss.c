#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
    int seconds;
    int nanoseconds;
} MyClock;

int main(void) {
    int shmid = shmget(1234, sizeof(Clock), IPC_CREAT | 0666);
    if (shmid <= 0) {
        fprintf(stderr,"Parent:... Error in shmget\n");
        exit(1);
    }

    MyClock *myClock = (MyClock *)shmat(shmid, NULL, 0);
    if (myClock <= 0) {
        fprintf(stderr,"Parent:... Error in shmat\n");
        exit(1);
    }

    shmdt(myClock);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
