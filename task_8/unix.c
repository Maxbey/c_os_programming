#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>

pthread_mutex_t output_mutex;
sem_t s_sem, w_sem;
int readers = 0;

char buff[12] = "++++++++++++";

void reader_thread(void *arg){
  char format[255];
  int iter = 0;

  for (int i = 0; i < 12; i++){
    sem_wait(&s_sem);
    readers++;

    if(readers == 1)
      sem_wait(&w_sem);

    sem_post(&s_sem);

    sprintf(format, "\033[%d;%dH", i + 1, (int) arg);
    printf("%s", format);
    printf("%c", buff[i]);
    printf("\n");

    sem_wait(&s_sem);
    readers--;

    if(!readers)
      sem_post(&w_sem);

    sem_post(&s_sem);

    usleep(600000);

    if(i == 11 && iter < 3){
        i = 0;
        iter++;
    }

  }
}

void writer_thread1(void *arg){
  char content[12] = "abcdefghijkl";

  for(int i = 0; i < 3; i++){
    sem_wait(&w_sem);

    strncpy(buff, content, 6);
    usleep(600000);
    strncpy(buff, content, 12);

    sem_post(&w_sem);
    usleep(3000000);
  }

}

void writer_thread2(void *arg){
  char content[12] = "ABCDEFGHIJKL";

  for(int i = 0; i < 3; i++){
    sem_wait(&w_sem);

    strncpy(buff, content, 6);
    usleep(600000);
    strncpy(buff, content, 12);

    sem_post(&w_sem);
    usleep(3000000);
  }
}

void writer_thread3(void *arg){
  char content[10] = "1234567890";

  for(int i = 0; i < 3; i++){
    sem_wait(&w_sem);

    strncpy(buff, content, 5);
    usleep(600000);
    strncpy(buff, content, 10);

    sem_post(&w_sem);
    usleep(3000000);
  }

}

void main(){
  pthread_t r_tid1, r_tid2, r_tid3;
  pthread_t w_tid1, w_tid2, w_tid3;

  pthread_mutex_init(&mutex, NULL);

  sem_init(&w_sem, 0, 1);
	sem_init(&s_sem, 0, 1);

  printf("\033[2J\n");

  pthread_create(&r_tid1, NULL, (void*)reader_thread, (void*)5);
  pthread_create(&r_tid2, NULL, (void*)reader_thread, (void*)15);
  pthread_create(&r_tid3, NULL, (void*)reader_thread, (void*)25);

  pthread_create(&w_tid1, NULL, (void*)writer_thread1, (void*)1);
  pthread_create(&w_tid2, NULL, (void*)writer_thread2, (void*)1);
  pthread_create(&w_tid3, NULL, (void*)writer_thread3, (void*)1);

  getchar();
}
