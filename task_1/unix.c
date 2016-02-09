#include "../helpers/unix/stdhandles.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void print_line(int, char *);

int main(){
    char input_buffer[255] = "";
    ssize_t readed;

    print_line(OUTPUT_HANDLE, "The unix standart input handle is: 0\n");
    print_line(OUTPUT_HANDLE, "The unix standart output handle is: 1\n");
    print_line(OUTPUT_HANDLE, "The unix standart error handle is: 2\n");

    print_line(OUTPUT_HANDLE, "\nJust type any text: ");

    readed = read(INPUT_HANDLE, input_buffer, sizeof(input_buffer));
    print_line(OUTPUT_HANDLE, "\nTyped text: ");
    write(OUTPUT_HANDLE, input_buffer, readed);

    return 0;
}

void print_line(int handle, char *line){
    write(handle, line, strlen(line));
}
