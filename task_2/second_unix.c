#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define INPUT_HANDLE 0
#define OUTPUT_HANDLE 1
#define ERROR_HANDLE 2

void read_write(int, int, int);

int main(int argc, char *argv[]){
    char input_buffer[255] = "";

    int first_handle = open(argv[1], O_RDONLY);
    int second_handle = dup(first_handle);
    int third_handle = open(argv[1], O_RDONLY);

    //Set offset
    lseek(first_handle, 10, SEEK_SET);

    write_line(OUTPUT_HANDLE, "First handle: ");
    write_int(OUTPUT_HANDLE, first_handle);

    write_line(OUTPUT_HANDLE, "\nSecond handle: ");
    write_int(OUTPUT_HANDLE, second_handle);

    write_line(OUTPUT_HANDLE, "\nThird handle: ");
    write_int(OUTPUT_HANDLE, third_handle);

    //Read from first handle
    write_line(OUTPUT_HANDLE, "\nRead from first: ");
    read_write(first_handle, OUTPUT_HANDLE, 7);

    //Read from second handle
    write_line(OUTPUT_HANDLE, "\nRead from second: ");
    read_write(second_handle, OUTPUT_HANDLE, 7);

    //Read from third handle
    write_line(OUTPUT_HANDLE, "\nRead from third: ");
    read_write(third_handle, OUTPUT_HANDLE, 7);

    write_line(OUTPUT_HANDLE, "\n\n");

    close(first_handle);
    close(second_handle);
    close(third_handle);

    return 0;
}

void write_line(int handle, char *line){
    write(handle, line, strlen(line));
}

void read_write(int read_handle, int write_handle, int bytes){
    char buff[255];

    read(read_handle, buff, bytes);
    write_line(write_handle, buff);
}

void write_int(int handle, int i){
    char buff[255] = "";
    sprintf(buff, "%d", i);

    write(handle, buff, strlen(buff));
}
