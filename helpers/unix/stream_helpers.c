#include <unistd.h>
#include <string.h>
#include "stream_helpers.h"

void stream_write(int handle, char *buff){
    write(handle, buff, strlen(buff));
}

void stream_read(int handle, char *buff, int bytes_cnt){
    read(handle, buff, bytes_cnt);
}
