#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "../helpers/alert_helpers.h"
#include "../helpers/unix/stdhandles.h"

/*
  Required:
  alert_helpers.c
*/

void read_write(int, int, char* buff, int);

int main(int argc, char *argv[]){
    int file_handle;
    char buff[255];

    struct flock lock = {F_WRLCK, SEEK_SET, 0, 0, 0};

    lock.l_pid = getpid();

    if ((file_handle = open(argv[1], O_RDWR)) == -1) {
        get_error_alert("Error: File not exist\n");
        exit(1);
    }

    get_success_alert("File \'%s\' opened...\n", argv[1]);

    printf("\nPress ENTER to get lock");
    getchar();
    printf("Trying to get lock...\n");

    if (fcntl(file_handle, F_SETLKW, &lock) == -1) {
        get_error_alert("Error on locking\n");
        exit(1);
    }
    get_success_alert("\nFile successfuly locked\n");

    printf("\nPress ENTER to read file...");
    getchar();

    read_write(file_handle, OUTPUT_HANDLE, buff, sizeof(buff));

    printf("\nPress ENTER to release lock: ");
    getchar();

    lock.l_type = F_UNLCK;

    if (fcntl(file_handle, F_SETLK, &lock) == -1) {
        get_error_alert("Error on unlocking\n");
        exit(1);
    }

    get_success_alert("File successfuly unlocked\n");
    close(file_handle);

    return 0;
}

void read_write(int read_handle, int write_handle, char *buff, int buffsize){
    ssize_t readed;

    readed = read(read_handle, buff, buffsize);
    write(write_handle, buff, readed);
}
