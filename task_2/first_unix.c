#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "../helpers/unix/stdhandles.h"

int main(int argc, char *argv[]){
    char input_buffer[255] = "";
    int file_handle = open(argv[1], O_RDWR|O_CREAT, 0666);

    ssize_t readed = read(INPUT_HANDLE, input_buffer, sizeof(input_buffer));
    write(file_handle, input_buffer, readed);

    close(file_handle);

    return 0;
}
