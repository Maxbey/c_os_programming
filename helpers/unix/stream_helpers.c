#include <unistd.h>
#include <string.h>
#include "stream_helpers.h"

ssize_t stream_write(int handle, char *buff, ssize_t bytes_cnt){
    return write(handle, buff, bytes_cnt);
}

ssize_t stream_read(int handle, char *buff, int buff_size){
    return read(handle, buff, buff_size);
}
