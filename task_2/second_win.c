#include  <windows.h>
#include <string.h>

HANDLE open_file(char *);
void read_write(HANDLE, HANDLE, int);

int main(int argc, char *argv[]){
  HANDLE output_handle = get_output_handle();

  HANDLE first_handle = open_file(argv[1]);
  HANDLE second_handle;
  HANDLE third_handle = open_file(argv[1]);

  DuplicateHandle(GetCurrentProcess(),
                  first_handle,
                  GetCurrentProcess(),
                  &second_handle,
                  0,
                  FALSE,
                  DUPLICATE_SAME_ACCESS);

  SetFilePointer(first_handle, (LONG) 10, NULL, FILE_BEGIN);

  read_write(first_handle, output_handle, 7);
  read_write(second_handle, output_handle, 7);
  read_write(third_handle, output_handle, 7);

  CloseHandle(first_handle);
  CloseHandle(second_handle);
  CloseHandle(third_handle);


  return 0;
}


HANDLE open_file(char *file_name){
  HANDLE file_handle = CreateFile(file_name,
                     GENERIC_READ,
                     FILE_SHARE_READ,
                     NULL,
                     OPEN_EXISTING,
                     FILE_ATTRIBUTE_NORMAL,
                     NULL);

  return file_handle;
}

void read_write(HANDLE read_handle, HANDLE write_handle, int bytes){
    char buff[7];
    DWORD readed, written;

    ReadFile(read_handle, buff, bytes, &readed, 0);
    WriteFile(write_handle, buff, readed, &written, 0);
    WriteFile(write_handle, "\n", 1, &written, 0);
}
