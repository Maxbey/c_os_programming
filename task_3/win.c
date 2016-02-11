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
        err_code = GetLastError();
        get_error_alert("Error on opening / code #%d", err_code);
        exit(1);
    }

    get_success_alert("\nFile \'%s\' is opened...", argv[1]);

    printf("\nPress ENTER to lock file");
    getchar();

    printf("\nTrying to get lock...");

    if (!LockFileEx(file_handle, LOCKFILE_EXCLUSIVE_LOCK, 0, 10000, 0, &overlapped))
    {
        err_code = GetLastError();
        get_error_alert("\nError on locking / code #%d", err_code);
        exit(1);
    }

    get_success_alert("\nFile successfuly locked\n");
    printf("\nFile contains: \n");

    read_write(file_handle, output_handle, buff, sizeof(buff));

    printf("\n\nPress ENTER to realese lock");
    getchar();

    UnlockFileEx(file_handle, 0, 10000, 0, &overlapped);
    get_success_alert("\n File successfuly unlocked");

    return 0;
}

void read_write(HANDLE read_handle, HANDLE write_handle, char *buff, int buffsize){
    DWORD readed, written;

    ReadFile(read_handle, buff, buffsize, &readed, 0);
    WriteFile(write_handle, buff, readed, &written, 0);
}
