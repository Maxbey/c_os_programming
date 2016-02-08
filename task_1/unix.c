#include "../helpers/unix/stdhandles.h"
/*
  Required:
  unix/stream_helpers
*/
int main(){
    char input_buffer[255] = "";

    stream_write(OUTPUT_HANDLE, "The unix standart input handle is: 0\n");
    stream_write(OUTPUT_HANDLE, "The unix standart output handle is: 1\n");
    stream_write(OUTPUT_HANDLE, "The unix standart error handle is: 2\n");

    stream_write(OUTPUT_HANDLE, "\nJust type any text: ");
    stream_read(INPUT_HANDLE, input_buffer, 255);
    stream_write(OUTPUT_HANDLE, "\nTyped text: ");
    stream_write(OUTPUT_HANDLE, input_buffer);

    return 0;
}
