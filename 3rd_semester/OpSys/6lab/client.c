#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/types.h>

int find(char* buffer, char* port, int size);
void menu();
struct msg {
  size_t clientId;
  size_t cash;
  char message[256];
};

int main(int argc, char *argv[]) {
  struct msg quest;
  size_t friendId, remCash;
  int act;
  char ans[256];
  void* requester;
  void* context;
      
  context = zmq_ctx_new();
  requester = zmq_socket(context, ZMQ_REQ);
  int rc = zmq_connect(requester, "tcp://localhost:5555");
      
  if (rc == 0) {
    printf("sucessfully connected\n");
  } else {
    perror("zmq_connect");
    printf("you saw that^, bye bye\n");
    
    zmq_close(requester);
    zmq_ctx_destroy(context);
    
    exit(1);
  }
  
  
  printf("client id?\n");
  scanf("%zu", &quest.clientId);
  quest.cash = 0;
  sprintf(quest.message, "ADD 0");
  zmq_msg_t clientReq;
  zmq_msg_init_size(&clientReq, sizeof(struct msg));
  memcpy(zmq_msg_data(&clientReq), &quest, sizeof(struct msg));

  printf("checking for user %zu\n", quest.clientId);
  zmq_msg_t reply;
  zmq_msg_send(&clientReq, requester, ZMQ_DONTWAIT);
  zmq_msg_close(&clientReq);

  zmq_msg_init(&reply);
  zmq_msg_recv(&reply, requester, 0);
  strcpy(ans, (char*)zmq_msg_data(&reply));
  
  if (strcmp(ans, "OK") == 0) {
    printf("Welcome\n");
  } else if (strcmp(ans, "ERR") == 0) {
    printf("some error, restart please\n");
    exit(1);
  } else {
    printf("hurr-durr-derp blurp\n");
  }
  zmq_msg_close(&reply);

  while(1) {
    menu();
    scanf("%d", &act);
    if (act == 1) {
      scanf("%zu", &remCash);
      sprintf(quest.message, "ADD %zu", remCash);
    } else if (act == 2) {
      scanf("%zu", &remCash);
      sprintf(quest.message, "RMV %zu", remCash);
    } else if (act == 3) {
      scanf("%zu %zu", &friendId, &remCash);
      sprintf(quest.message, "GFT %zu %zu", friendId, remCash);
    } else if (act == 4) {
      sprintf(quest.message, "STS");
    } else if (act == 5) {
      break;
    } else {
      continue;
    }

    zmq_msg_init_size(&clientReq, sizeof(struct msg));
    memcpy(zmq_msg_data(&clientReq), &quest, sizeof(struct msg));

    printf("sending %s\n", quest.message);
    zmq_msg_send(&clientReq, requester, 0);
    zmq_msg_close(&clientReq);

		zmq_msg_init(&reply);
		zmq_msg_recv(&reply, requester, 0);
		size_t repSize = zmq_msg_size(&reply);
    strcpy(ans, (char*)zmq_msg_data(&reply));
		printf("Received: - %zu %s\n", repSize, ans);
    if (strcmp(ans, "OK") == 0) {
      printf("Operation went sucessfulyyyyy\n");
    } else if (strcmp(ans, "NISHEBROD") == 0) {
      printf("get some money scrub\n");
    } else if (strcmp(ans, "NOFRND") == 0) {
      printf("wrong user m8\n");
    } else if (strcmp(ans, "ERR") == 0) {
      printf("some error\n");
      exit(1);
    } else if (strncmp(ans, "ID", 2) == 0) {
      sscanf(ans, "ID %zu CSH %zu", &friendId, &remCash);
      printf("Your stats are: id - %zu\n cash amount - %zu\n", friendId, remCash);
    } else {
      printf("hurr-durr-derp\n");
    }
		zmq_msg_close(&reply);

  }

  zmq_close(requester);
  zmq_ctx_destroy(context);
  return 0;
}

void menu() {
  printf("Commands\n");
  printf("1) Add Cash\n");
  printf("2) Draw Cash\n");
  printf("3) Gift ToId Cash\n");
  printf("4) Account stats\n");
  printf("5) Exit\n");
}
