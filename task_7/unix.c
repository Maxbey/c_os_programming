#include <pthread.h>
#include <stdio.h>

char dictionary[] = "abcdefghijklmnoprstv";
pthread_mutex_t mutex;

void thread1(void *arg){
  int k, j;

  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

  for (k=0; k < 20; k++){
    pthread_mutex_lock(&mutex);
    printf("\033[%d;5H",k+1);
    for (j=0; j < (int) arg * 2; j++){
      get_success_alert("%c",dictionary[k]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
    usleep(1000000);
  }
}

void thread2(void *arg){
  int k, j;

  for (k=0; k<20; k++){
    pthread_mutex_lock(&mutex);
    printf("\033[%d;15H",k+1);
    for (j=0; j < (int) arg * 2; j++){
      get_warning_alert("%c",dictionary[k]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
    usleep(1000000);
  }
}

void thread3(void *arg){
  int k, j;

  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

  for (k=0; k < 20; k++){
    if(k == 13){
      pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    }
    if(k == 16 || k == 17)
      pthread_testcancel();

    pthread_mutex_lock(&mutex);
    printf("\033[%d;30H",k+1);
    for (j=0; j < (int) arg * 2; j++){
      get_error_alert("%c",dictionary[k]);
    }

    printf("\n");
    pthread_mutex_unlock(&mutex);
    usleep(1000000);
  }
}

void main(){
  pthread_t tid1, tid2, tid3;
  int k;
  int rc;

  pthread_mutex_init(&mutex, NULL);

  rc = pthread_create(&tid1, NULL, (void*)thread1, (void*)2);
  rc = pthread_create(&tid2, NULL, (void*)thread2, (void*)3);
  rc = pthread_create(&tid3, NULL, (void*)thread3, (void*)4);



  printf("\033[2J\n");
  for (k=0; k<20; k++){
    if(k == 6){
      printf("\033[0;50H");
      printf("Trying to cancel the first thread...");
      int a = pthread_cancel(tid1);
    }

    if(k == 11){
      printf("\033[1;50H");
      printf("Trying to cancel the second thread...");
      pthread_cancel(tid3);
    }

    pthread_mutex_lock(&mutex);
    printf("\033[%d;1H",k+1);
    printf("%c\n",dictionary[k]);
    pthread_mutex_unlock(&mutex);
    usleep(1000000);
  }
  getchar();
}
