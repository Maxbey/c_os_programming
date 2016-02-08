#include  <string.h>
#include  "stream_helpers.h"

void stream_write(HANDLE handle, char *line){
    DWORD actlen = strlen(line);

    WriteFile(handle, line, actlen, &actlen, 0);
}

void stream_write_int(HANDLE handle, int i){
    char buff[255] = "";
    itoa(i, buff, 10);
    DWORD actlen = strlen(buff);

    WriteFile(handle, buff, actlen, &actlen, 0);
}

void stream_read(HANDLE handle, char *buff, int bytes_cnt){
  DWORD readed;

  ReadFile(handle, buff, bytes_cnt, &readed, 0);
}
