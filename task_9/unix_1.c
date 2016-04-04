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

  char text_for_share[] = "This is shared text";

  memory_handle = shmget(18011970, 100, IPC_CREAT | 0600);

  if(memory_handle == -1){
    get_error_alert("Error on mapping creating");
    exit(1);
  }
  get_success_alert("\nMapping successfully created\n");

  mem_pointer = shmat(memory_handle, NULL, 0);
  if(mem_pointer == -1){
    get_error_alert("Error getting pointer");
    exit(1);
  }

  get_success_alert("\nMemory pointer is %d\n", mem_pointer);

  sem = sem_open("memory_sem", O_CREAT, 0644, 1);
  sem_wait(sem);

  usleep(10000000);

  strcpy(mem_pointer, text_for_share);

  sem_post(sem);

  get_warning_alert("\nData written to shared memory. The semaphore is released...\n");

  getchar();
  sem_close(sem);
  sem_unlink("memory_sem");
  shmctl(memory_handle, IPC_RMID, NULL);


  return 0;
}
