#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>

pthread_mutex_t output_mutex;
sem_t s_sem, w_sem;
int readers = 0;

struct thread_config {
  int position;
  int delay;
};

char buff[12] = "++++++++++++";

void reader_thread(void *args){
  char format[255];
  int iter = 0;

  struct thread_config *config = args;

  for (int i = 0; i < 12; i++){
    sem_wait(&s_sem);
    readers++;

    if(readers == 1)
      sem_wait(&w_sem);

    sem_post(&s_sem);

    sprintf(format, "\033[%d;%dH", i + 1, config->position);
    printf("%s", format);
    printf("%c", buff[i]);
    printf("\n");

    sem_wait(&s_sem);
    readers--;

    if(!readers)
      sem_post(&w_sem);

    sem_post(&s_sem);

    usleep(config->delay * 100000);

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
    usleep((int)arg * 100000);
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
    usleep((int)arg * 100000);
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
    usleep((int)arg * 100000);
    strncpy(buff, content, 10);

    sem_post(&w_sem);
    usleep(3000000);
  }

}

void main(){
  pthread_t r_tid1, r_tid2, r_tid3;
  pthread_t w_tid1, w_tid2, w_tid3;

  pthread_mutex_init(&output_mutex, NULL);

  sem_init(&w_sem, 0, 1);
	sem_init(&s_sem, 0, 1);

  printf("\033[2J\n");

  struct thread_config reader1_config;
  struct thread_config reader2_config;
  struct thread_config reader3_config;

  reader1_config.position = 5;
  reader1_config.delay = 1;

  reader2_config.position = 15;
  reader2_config.delay = 2;

  reader3_config.position = 25;
  reader3_config.delay = 3;

  pthread_create(&r_tid1, NULL, (void*)reader_thread, (void *) &reader1_config);
  pthread_create(&r_tid2, NULL, (void*)reader_thread, (void *) &reader2_config);
  pthread_create(&r_tid3, NULL, (void*)reader_thread, (void *) &reader3_config);

  pthread_create(&w_tid1, NULL, (void*)writer_thread1, (void*)4);
  pthread_create(&w_tid2, NULL, (void*)writer_thread2, (void*)5);
  pthread_create(&w_tid3, NULL, (void*)writer_thread3, (void*)6);

  getchar();
}
