#include <windows.h>

extern void stream_write(HANDLE, char *);
extern void stream_write_int(HANDLE, int);
extern void stream_read(HANDLE, char *, int);
