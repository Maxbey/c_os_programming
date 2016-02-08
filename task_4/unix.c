#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "../helpers/iohelpers.h"

#define INPUT_HANDLE 0
#define OUTPUT_HANDLE 1

int main(int argc, char *argv[]){
    int file_handle;
    struct flock lock = {F_WRLCK, SEEK_SET, 0, 0, 0};

    lock.l_pid = getpid();

    if ((file_handle = open(argv[1], O_RDWR)) == -1) {
        printf("%sError: File not exist\n", KRED);
        exit(1);
    }

    printf("%sFile \'%s\' opened...\n\n", KGRN, argv[1]);

    printf("%sPress ENTER to try to get lock: ", KNRM);
    getchar();
    printf("Trying to get lock...\n");

    if (fcntl(file_handle, F_SETLKW, &lock) == -1) {
        printf("%sError on locking\n", KRED);
        exit(1);
    }

    printf("%sFile successfuly locked\n", KGRN);

    printf("Readed from file: ");
    read_write(file_handle, OUTPUT_HANDLE, 1);

    printf("%sPress ENTER to release lock: ", KNRM);
    getchar();

    lock.l_type = F_UNLCK;

    if (fcntl(file_handle, F_SETLK, &lock) == -1) {
        printf("%sError on unlocking\n", KRED);
        exit(1);
    }

    printf("%sFile successfuly unlocked.\n", KGRN);

    close(file_handle);




    return 0;
}

void read_write(int read_handle, int write_handle, int bytes){
    char buff[255];

    read(read_handle, buff, bytes);
    write_line(write_handle, buff);
}

void write_line(int handle, char *line){
    write(handle, line, strlen(line));
}
