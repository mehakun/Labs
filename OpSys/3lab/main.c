#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct TSmth {
  int* deck;
  int equalCount;
  int iterations;
  pthread_mutex_t mutex;
}TSmth;

void* randr(void* arg) {
  pthread_mutex_lock(&((TSmth*)arg)->mutex);
  double scaled;
  
  for (int i = 0; i < ((TSmth*)arg)->iterations;i++) {
    scaled = (double)rand()/RAND_MAX;
    ((TSmth*)arg)->deck[i] = 52*scaled;
  }
  
  pthread_mutex_unlock(&((TSmth*)arg)->mutex);
  pthread_exit(NULL);
}

void* equal(void* arg) {
  pthread_mutex_lock(&((TSmth*)arg)->mutex);
  
  for (int i = 0; i < ((TSmth*)arg)->iterations; i += 2) {
    if (((TSmth*)arg)->deck[i] == ((TSmth*)arg)->deck[i + 1])
      ((TSmth*)arg)->equalCount++;
  }
  
  pthread_mutex_unlock(&((TSmth*)arg)->mutex);
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  pthread_t cardsShuffle, cardsEqual;
  TSmth deck;
  deck.iterations = atoi(argv[1]);
  deck.equalCount = 0;
  deck.deck = (int*)malloc(sizeof(int) * deck.iterations * 2);

  if (pthread_mutex_init(&deck.mutex, NULL)) {
    perror("pthread_mutex_init");
    exit(-1);
  }
  if (pthread_create(&cardsShuffle, NULL, randr, (void*)&deck)) {
    perror("pthread_create(cardsShuffle)");
    exit(-1);
  }
  if (pthread_create(&cardsEqual, NULL, equal, (void*)&deck)) {
    perror("pthread_create(cardsEqual)");
    exit(-1);
  }

  pthread_join(cardsShuffle, NULL);
  pthread_join(cardsEqual, NULL);
  printf("Chance is %f\n", deck.equalCount / (deck.iterations * 1.0));
  
  pthread_mutex_destroy(&deck.mutex);
  free(deck.deck);
  pthread_exit(NULL);
}
