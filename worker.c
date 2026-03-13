#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct {
    int seconds;
    int nanoseconds;
} MyClock;

int main(int argc, char *argv[]) {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    int inputSec = atoi(argv[1]);
    int inputNano = atoi(argv[2]);

    printf("Worker starting, PID: %d, PPID: %d\n", pid, ppid);
    printf("Called with:\n");
    printf("Intervals: %d seconds, %d nanoseconds\n", inputSec, inputNano);

    int shmid = shmget(1234, sizeof(MyClock), 0666);
    if (shmid < 0) {
        fprintf(stderr,"Worker: shmget error\n");
        exit(1);
    }

    MyClock *myClock = (MyClock *)shmat(shmid, NULL, 0);
    if (myClock <= 0 ) {
        perror("worker: shmat error");
        return 1;
    }

    int startSec = myClock->seconds;
    int startNano = myClock->nanoseconds;

    //calculate termination time
    int endSec = startSec + inputSec;
    int endNano = startNano + inputNano;

    printf("WORKER PID:%d PPID:%d\n", pid, ppid);
    printf("SysClockS: %d SysclockNano: %d TermTimeS: %d TermTimeNano: %d\n", startSec, startNano, endSec, endNano);
    printf("--Just Starting\n");

    int lastSec = startSec;

    while (1) {
        int currentSec = myClock->seconds;
        int currentNano = myClock->nanoseconds;

        if (currentSec != lastSec) {
            printf("WORKER PID:%d PPID:%d\n", pid, ppid);
            printf("SysClockS: %d SysclockNano: %d TermTimeS: %d TermTimeNano: %d\n", currentSec, currentNano, endSec, endNano);
            printf("--%d seconds have passed since starting\n", currentSec - startSec);
            lastSec = currentSec;
        }

        //check for termination condition
        if (currentSec > endSec || (currentSec == endSec && currentNano >= endNano)) {
            printf("WORKER PID:%d PPID:%d\n", pid, ppid);
            printf("SysClockS: %d SysClockNano: %d\n", currentSec, currentNano);
            printf("--Terminating\n");
            break;
        }
    }
    
    shmdt(myClock);
    return 0;
}
