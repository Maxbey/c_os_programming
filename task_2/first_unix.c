#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../helpers/unix/stdhandles.h"

/*
  Required:
  stream_helpers.c
*/

int main(int argc, char *argv[]){
    char input_buffer[255] = "";
    int file_handle = open(argv[1], O_RDWR|O_CREAT, 0666);

    stream_read(INPUT_HANDLE, input_buffer, 255);
    stream_write(file_handle, input_buffer);

    close(file_handle);

    return 0;
}
