#include <stdlib.h>
#include <windows.h>
#include <winerror.h>

/*
  Required:
  win/handle_helpers.c
  alert_helpres
*/

void read_write(HANDLE, HANDLE, char *, int);

int main(int argc, char *argv[]){
    char buff[255] = "";
    HANDLE file_handle;
    DWORD err_code;
    OVERLAPPED overlapped;
    HANDLE output_handle = get_output_handle();

    memset(&overlapped, 0, sizeof(overlapped));

    file_handle = CreateFile(argv[1],
                       GENERIC_READ,
                       FILE_SHARE_READ,
                       NULL,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

    if(file_handle == INVALID_HANDLE_VALUE)
    {
        print_error_alert(output_handle, "Error on opening");
        exit(1);
    }

    if(!LockFile(file_handle, 0, 0, 10, 10))
    {
      print_warning_alert(output_handle, "File is locked! Waiting...");
      if (!LockFileEx(file_handle, LOCKFILE_EXCLUSIVE_LOCK, 0, 10000, 0, &overlapped))
      {
          err_code = GetLastError();
          print_error_alert(output_handle, "Error on locking");
          exit(1);
      }
    }
    print_success_alert(output_handle, "File successfuly locked");
    Sleep(500);
    printf("\nFile contains:\n");
    read_write(file_handle, output_handle, buff, sizeof(buff));

    Sleep(7000);

    UnlockFileEx(file_handle, 0, 10000, 0, &overlapped);
    print_success_alert(output_handle, "File successfuly unlocked");

    return 0;
}

void read_write(HANDLE read_handle, HANDLE write_handle, char *buff, int buffsize){
    DWORD readed, written;

    ReadFile(read_handle, buff, buffsize, &readed, 0);
    WriteFile(write_handle, buff, readed, &written, 0);
}
