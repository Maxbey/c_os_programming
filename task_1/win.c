#include  <windows.h>
#include <string.h>

/*
  Required:
  win/handle_helpers,
  alert_helpers
*/

DWORD write_line(HANDLE, char*);

DWORD print_string(HANDLE, char *);

DWORD print_int(HANDLE, int);

int main(){
    char input_buffer[255] = "";

    HANDLE input_handle = get_input_handle();
    HANDLE output_handle = get_output_handle();

    DWORD readed, written;

    if(input_handle == -1 || output_handle == -1){
      get_error_alert("Wrong i/o handle");
    }

    print_string(output_handle, "The win standart input handle is ");
    print_int(output_handle, input_handle);

    print_string(output_handle, "\nThe win standart output handle is ");
    print_int(output_handle, output_handle);

    print_line(output_handle, "\n\nJust type any text: ");

    ReadFile(input_handle, input_buffer, sizeof(buffer), &readed, 0);
    print_string(output_handle, "\nTyped text is: ");

    WriteFile(output_handle, input_buffer, readed, &written, 0);

    return 0;
}

DWORD write_line(HANDLE handle, char* buff){
    DWORD to_write = strlen(buff);
    DWORD written;

    WriteFile(handle, buff, to_write, &written, 0);

    return written;
}

DWORD print_string(HANDLE handle, char *string){
    return write_line(handle, string);
}

DWORD print_int(HANDLE handle, int i){
    char num_buff[30] = "";
    itoa(i, buff, 10);

    return write_line(handle, num_buff);
}
