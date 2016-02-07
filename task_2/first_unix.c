#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define INPUT_HANDLE 0
#define OUTPUT_HANDLE 1
#define ERROR_HANDLE 2

int main(int argc, char *argv[]){
    char input_buffer[255] = "";
    int file_handle = open(argv[1], O_RDWR|O_CREAT, 0666);

    read(INPUT_HANDLE, input_buffer, sizeof(input_buffer));
    write(file_handle, input_buffer, strlen(input_buffer));

    close(file_handle);

    return 0;
}
