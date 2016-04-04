#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <semaphore.h>
#include "../helpers/alert_helpers.h"

int main(){
  sem_t *sem;

  char *mem_pointer;
  int memory_handle;

  memory_handle = shmget(18011970, 100, 0600);

  if(memory_handle == -1){
    get_error_alert("Cannot find shared memory\n");
    exit(1);
  }
  get_success_alert("\nShared memory opened\n");

  mem_pointer = shmat(memory_handle, NULL, SHM_RDONLY);
  if(mem_pointer == -1){
    get_error_alert("Error getting pointer");
    exit(1);
  }

  get_success_alert("\nMemory pointer is %d\n", mem_pointer);

  sem = sem_open("memory_sem", 0);
  get_warning_alert("\nWaiting for semaphore...\n");
  sem_wait(sem);

  printf("Readed from memory: %s", mem_pointer);

  sem_post(sem);
  sem_close(sem);
  getchar();

  return 0;
}
