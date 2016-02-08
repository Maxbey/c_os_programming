#include  <windows.h>
#include <winerror.h>

/*
  Required:
  win/handle_helpers,
  win/stream_helpers,
  alert_helpers
*/

int main(){
    char input_buffer[255] = "";

    HANDLE input_handle = get_input_handle();
    HANDLE output_handle = get_output_handle();

    if(input_handle == -1 || output_handle == -1){
      get_error_alert("Wrong i/o handle");
    }

    stream_write(output_handle, "The win standart input handle is ");
    stream_write_int(output_handle, input_handle);

    stream_write(output_handle, "\nThe win standart output handle is ");
    stream_write_int(output_handle, output_handle);

    stream_write(output_handle, "\n\nJust type any text: ");

    stream_read(input_handle, input_buffer, 255);
    stream_write(output_handle, "\nTyped text is: ");
    stream_write(output_handle, input_buffer);

    return 0;
}
