#include <windows.h>
#include <winerror.h>
#include <stdlib.h>

int main(){
  char *mem_pointer;
  HANDLE memory_handle;
  HANDLE event_handle;

  memory_handle = OpenFileMapping(FILE_MAP_READ, FALSE, "sharedMemory");

  if(!memory_handle){
    get_error_alert("Error on file mapping opening | code # %d", GetLastError());
    exit(1);
  }
  get_success_alert("\nFile mapping successfully opened\n");

  mem_pointer = MapViewOfFile(memory_handle, FILE_MAP_READ, 0, 0, 0);

  if(!mem_pointer){
    get_error_alert("Error on view of mapping | code # %d", GetLastError());
    exit(1);
  }
  get_success_alert("\nMemory pointer is %d\n", mem_pointer);

  event_handle = OpenEvent(EVENT_ALL_ACCESS, TRUE, "event");
  get_warning_alert("\nWaiting for event...\n\n");
  WaitForSingleObject(event_handle, INFINITE);

  printf("Data from shared memory: %s", mem_pointer);

  return 0;
}
