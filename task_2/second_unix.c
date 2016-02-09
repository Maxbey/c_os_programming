#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../helpers/unix/stdhandles.h"

void read_write(int, int, int);

int main(int argc, char *argv[]){
    char input_buffer[255] = "";

    int first_handle = open(argv[1], O_RDONLY);
    int second_handle = dup(first_handle);
    int third_handle = open(argv[1], O_RDONLY);

    //Set offset
    lseek(first_handle, 10, SEEK_SET);

    printf("First handle %d\n", first_handle);
    printf("Second handle %d\n", second_handle);
    printf("Third handle %d\n\n", third_handle);

    read_write(first_handle, OUTPUT_HANDLE, 7);

    read_write(second_handle, OUTPUT_HANDLE, 7);

    read_write(third_handle, OUTPUT_HANDLE, 7);

    close(first_handle);
    close(second_handle);
    close(third_handle);

    return 0;
}

void read_write(int read_handle, int write_handle, int bytes){
    char buff[7];
    ssize_t readed;

    readed = read(read_handle, buff, bytes);
    write(write_handle, buff, readed);
    write(write_handle, "\n", 1);
}
