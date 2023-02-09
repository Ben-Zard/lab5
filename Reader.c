#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define MAX_SIZE 100

char *ptr;
int shmid;
char prev_str[MAX_SIZE];

int main() {
    key_t key = ftok("writer.c", 'R');
    shmid = shmget(key, MAX_SIZE, 0666);
    ptr = shmat(shmid, NULL, 0);
    strcpy(prev_str, ptr);

    while (1) {
        if (strcmp(ptr, prev_str) != 0) {
            printf("String from Writer: %s\n", ptr);
            strcpy(prev_str, ptr);
        }
    }

    return 0;
}
