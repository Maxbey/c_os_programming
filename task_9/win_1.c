#include <windows.h>
#include <winerror.h>
#include <string.h>

int main(){
  char *mem_pointer;
  char *add_memory = NULL;
  char offset;

  char dictionary[] = "abcdefghijklmnoprstv";

  HANDLE memory_handle;
  HANDLE event_handle;

  char text_for_share[] = "This is shared text";

  memory_handle = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL,
            PAGE_READWRITE, 0, sizeof(text_for_share), "sharedMemory");

  if(!memory_handle){
    get_error_alert("Error on file mapping creating | code # %d", GetLastError());
    exit(1);
  }

  get_success_alert("\nFile mapping successfully created\n");

  mem_pointer = MapViewOfFile(memory_handle, FILE_MAP_WRITE, 0, 0, 0);

  if(!mem_pointer){
    get_error_alert("Error on view of mapping | code # %d", GetLastError());
    exit(1);
  }

  get_success_alert("\nMemory pointer is %d\n", mem_pointer);

  event_handle = CreateEvent(NULL, FALSE, FALSE, "event");

  Sleep(10000);

  strcpy(mem_pointer, text_for_share);
  PulseEvent(event_handle);

  get_warning_alert("\nWritten text to memory, event pulsed\n");

  add_memory = VirtualAlloc(NULL, 1000, MEM_COMMIT, PAGE_READWRITE);

  if(add_memory == NULL){
    get_error_alert("\nError on memory requesting");
    exit(1);
  }

  get_success_alert("\nAdditional memory successfully commited\n\n");

  for(int i = 0; i < 15; i++)
  {
    *(add_memory + 400 * (i + 1)) = dictionary[i];
    printf("Char %c written | Memory size is %d\n", dictionary[i], 400 * (i + 1));
    Sleep(1000);
  }

  return 0;
}
