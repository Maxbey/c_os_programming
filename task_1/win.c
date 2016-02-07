typedef int bool;
#define true 1
#define false 0

#include  <windows.h>
#include  <string.h>

bool check_handle(HANDLE);
void write_line(HANDLE, char *);
void write_int(HANDLE, int);
void read_line(HANDLE, char *);

int main(){
    HANDLE input_handle, output_handle;
    char input_buffer[255] = "";

    input_handle = GetStdHandle(STD_INPUT_HANDLE);
    if(!check_handle(input_handle))
        return 0;

    output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!check_handle(output_handle))
        return 0;

    write_line(output_handle, "The win standart input handle is ");
    write_int(output_handle, input_handle);

    write_line(output_handle, "\nThe win standart output handle is ");
    write_int(output_handle, output_handle);

    write_line(output_handle, "\n\nJust type any text: ");

    read_line(input_handle, input_buffer, sizeof(input_buffer));
    write_line(output_handle, "\nTyped text is: ");
    write_line(output_handle, input_buffer);

    return 0;
}

bool check_handle(HANDLE handle){
    if(handle == INVALID_HANDLE_VALUE)
        return false;

    return true;
}

void write_line(HANDLE handle, char *line){
    DWORD actlen = strlen(line);

    WriteFile(handle, line, actlen, &actlen, 0);
}

void write_int(HANDLE handle, int i){
    char buff[255] = "";
    itoa(i, buff, 10);
    DWORD actlen = strlen(buff);

    WriteFile(handle, buff, actlen, &actlen, 0);
}

void read_line(HANDLE handle, char *buff, int buffsize){
  DWORD actlen = buffsize;

  ReadFile(handle, buff, actlen, &actlen, 0);
}
