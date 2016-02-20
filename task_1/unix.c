#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_line(int, char *);

int main() {
  char input_buffer[255] = "";
  ssize_t readed;
  if(isatty(0) !=0 )
    print_line(2, "Type any text: ");

  readed = read(0, input_buffer, sizeof(input_buffer));
  print_line(1, "Typed text: ");
  write(1, input_buffer, readed);

  return 0;
}

void print_line(int handle, char *line){
  write(handle, line, strlen(line));
};
