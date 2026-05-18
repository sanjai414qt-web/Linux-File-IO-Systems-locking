//C program that illustrates files locking goes here

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

void display_lslocks() {
    printf("\nCurrent 'lslocks' output:\n");
    fflush(stdout);
    system("lslocks");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (flock(fd, LOCK_SH) == -1) {
        perror("Error acquiring shared lock");
        exit(EXIT_FAILURE);
    }
    printf("Acquired shared lock\n");
    display_lslocks();
    sleep(1);
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        perror("Error upgrading lock");
    } else {
        printf("Upgraded to exclusive lock\n");
        display_lslocks();
    }
    flock(fd, LOCK_UN);
    printf("Unlocked\n");
    close(fd);
    return 0;
}

