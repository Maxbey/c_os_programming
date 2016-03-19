#include  <windows.h>
#include <string.h>

int main(int argc, char *argv[]){
    char input_buffer[255];

    HANDLE file_handle;
    DWORD err_code;
    DWORD readed, written;

    HANDLE input_handle = get_input_handle();

    file_handle = CreateFile(argv[1],
                       GENERIC_WRITE,
                       FILE_SHARE_READ,
                       NULL,
                       CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

    if(file_handle == INVALID_HANDLE_VALUE)
    {
        err_code = GetLastError();
        get_error_alert("Error on opening / code #%d", err_code);
        exit(1);
    }

    ReadFile(input_handle, input_buffer, sizeof(input_buffer), &readed, 0);
    WriteFile(file_handle, input_buffer, readed, &written, 0);

    CloseHandle(file_handle);

    return 0;
}
