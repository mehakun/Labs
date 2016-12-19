#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define WEIRD_CONST 10

typedef struct TSmth {
  int* deck;
  int isEqual;
  int iterations;
} TSmth;

void* randr(void* arg) {
  double scaled;

  for (int i = 0; i < ((TSmth*)arg)->iterations; i++) {
    scaled = (double)rand()/RAND_MAX;
    ((TSmth*)arg)->deck[i] = 52*scaled;

  }
  for (int i = 0; i < ((TSmth*)arg)->iterations; i += 2) {
    if (((TSmth*)arg)->deck[i] == ((TSmth*)arg)->deck[i + 1])
      ((TSmth*)arg)->isEqual++;
  }
  
  pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
  if (argc == 1 || argc == 2 || argc > 3) {
    printf("Usage: one ExperimentsNumber ThreadsNumber\n");
    exit(0);
  }
  
  int iterations = atoi(argv[1]);
  int threads = atoi(argv[2]);
  double result = 0;
  if (iterations < 0 || threads < 0 ||
      threads == 0 || iterations == 0) {
    printf("Change your numbers dumb4SS\n");
    exit(-1);
  }
  if (iterations <= threads) {
    TSmth arr[iterations];
    pthread_t process[iterations];
    for (int i = 0; i < iterations; i++) {
      arr[i].deck = malloc(sizeof(int) * 2);
      arr[i].isEqual = 0;
      arr[i].iterations = 2;
      
      if (pthread_create(&process[i], NULL, randr, (void*)&arr[i])) {
        perror("pthread_create");
        exit(-1);
      }

    }

    for (int i = 0; i < iterations;i++) {
      pthread_join(process[i], NULL);
      result += arr[i].isEqual;
    }
    printf("Chance is %f\n", result / iterations);

  } else {
    TSmth arr[threads];
    pthread_t process[threads];
    //    printf("iterations / threads %d\n", iterations / threads);
    for (int i = 0; i < threads - 1; i++) {
      arr[i].deck = malloc(sizeof(int) * 2 * (iterations / threads));
      arr[i].isEqual = 0;
      arr[i].iterations = 2 * (iterations / threads);
      
      if (pthread_create(&process[i], NULL, randr, (void*)&arr[i])) {
        perror("pthread_create");
        exit(-1);
      }

    }

    for (int i = 0; i < threads - 1;i++) {
      pthread_join(process[i], NULL);
      result += arr[i].isEqual;
      free(arr[i].deck);
    }
    //    printf("(iterations - iterations / threads-1) %d\n", (iterations - iterations / threads * threads));
    arr[threads-1].deck = malloc(sizeof(int) * 2 * (iterations - iterations / threads * threads));
    arr[threads-1].isEqual = 0;
    arr[threads-1].iterations = 2 * (iterations - iterations / threads * threads);
    if (pthread_create(&process[threads-1], NULL, randr, (void*)&arr[threads-1])) {
      perror("pthread_create");
      exit(-1);
    }

    pthread_join(process[threads-1], NULL);
    result += arr[threads-1].isEqual;
    free(arr[threads-1].deck);
    printf("Chance is %f\n", result / iterations);
    
  }  
  
  exit(0);
}
