#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX_SIZE 100

char *ptr;
int shmid;

void release_resources() {
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    printf("\nAll system resources released.\n");
    exit(0);
}

void handle_sigint(int sig) {
    release_resources();
}

int main() {
    char buffer[MAX_SIZE];

    signal(SIGINT, handle_sigint);

    key_t key = ftok("writer.c", 'R');
    shmid = shmget(key, MAX_SIZE, 0666|IPC_CREAT);
    ptr = shmat(shmid, NULL, 0);

    while (1) {
        printf("Enter a string: ");
        scanf("%s", buffer);
        if (strcmp(buffer, "quit") == 0) {
            release_resources();
        }

        strcpy(ptr, buffer);
    }

    return 0;
}

