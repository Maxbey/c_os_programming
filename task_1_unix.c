#include <unistd.h>
#include <string.h>

#define INPUT_HANDLE 0
#define OUTPUT_HANDLE 1
#define ERROR_HANDLE 2

void write_line(int, char *);

int main(){
    char input_buffer[255] = "";

    write_line(OUTPUT_HANDLE, "The unix standart input handle is: 0\n");
    write_line(OUTPUT_HANDLE, "The unix standart output handle is: 1\n");
    write_line(OUTPUT_HANDLE, "The unix standart error handle is: 2\n");

    write_line(OUTPUT_HANDLE, "\nJust type any text: ");
    read(INPUT_HANDLE, input_buffer, sizeof(input_buffer));
    write_line(OUTPUT_HANDLE, "\nTyped text: ");
    write_line(OUTPUT_HANDLE, input_buffer);

    return 0;
}

void write_line(int handle, char *line){
    write(handle, line, strlen(line));
}
