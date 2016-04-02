#include <pthread.h>
#include <stdio.h>
#include <string.h>

char dictionary[] = "abcdefghijklmnoprstv";

pthread_mutex_t mutex;

struct thread_config {
  char color[8];
  char position[11];
  int print_times;
};

void _log(char *);

void thread1_3(void *args){
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  char buff[255];

  struct thread_config *config = args;

  for (int i = 0; i < 20; i++){
    if(i == 13){
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
      pthread_testcancel();
    }


    pthread_mutex_lock(&mutex);
    sprintf(buff, config->position, i + 1);
    printf("%s", buff);
    printf("%s", config->color);

    for (int j = 0; j < config->print_times; j++){
      printf("%c", dictionary[i]);
    }

    printf("\n");
    pthread_mutex_unlock(&mutex);
    usleep(1000000);
  }
}

void thread2(void *arg){

  for (int i = 0; i < 20; i++){
    pthread_mutex_lock(&mutex);
    printf("\033[%d;15H", i + 1);
    for (int j = 0; j < (int) arg * 2; j++){
      get_warning_alert("%c", dictionary[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
    usleep(1000000);
  }
}

void main(){
  pthread_t tid1, tid2, tid3;
  int rc;

  struct thread_config config1;
  struct thread_config config3;

  strcpy(config1.color, "\x1B[32m");
  strcpy(config1.position, "\033[%d;5H");
  config1.print_times = 4;

  strcpy(config3.color, "\x1B[31m");
  strcpy(config3.position, "\033[%d;30H");
  config3.print_times = 8;

  pthread_mutex_init(&mutex, NULL);

  rc = pthread_create(&tid1, NULL, (void*)thread1_3, (void *) &config1);
  rc = pthread_create(&tid2, NULL, (void*)thread2, (void *) 3);
  rc = pthread_create(&tid3, NULL, (void*)thread1_3, (void *) &config3);



  printf("\033[2J\n");
  for (int i = 0; i < 20; i++){
    if(i == 6){
      _log("Trying to cancel the first thread on step 6");
      int a = pthread_cancel(tid1);
    }

    if(i == 11){
      _log("Trying to cancel the third thread on step 11");
      pthread_cancel(tid3);
    }

    pthread_mutex_lock(&mutex);
    printf("\033[%d;1H", i + 1);
    printf("\x1B[0m");
    printf("%c\n", dictionary[i]);
    pthread_mutex_unlock(&mutex);
    usleep(1000000);
  }
  getchar();
}

void _log(char *message)
{
  pthread_mutex_lock(&mutex);
  printf("\033[0;50H");
  printf("\x1B[0m");
  printf("%s", message);
  pthread_mutex_unlock(&mutex);
}
