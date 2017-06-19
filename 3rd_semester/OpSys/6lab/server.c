#include "bst.h"
#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include <signal.h>
volatile sig_atomic_t flag = 0;

void my_function(int sig){
  flag = 1;
}

struct msg {
  size_t clientId;
  size_t cash;
  char message[256];
};

int main(int argc, char *argv[]) {
  FILE* fp = fopen("./db", "r+");
  int rc;
  struct BST* root = NULL;
  struct BST* node = NULL;
  struct BST* friend = NULL;
  struct client tmp;
  struct msg* quest;
  zmq_msg_t reply;
  zmq_msg_t sms;
  size_t friendId, remCash;
  char ans[256];
  void* context = zmq_ctx_new();
  void* responder = zmq_socket(context, ZMQ_REP);
  rc = zmq_bind(responder, "tcp://*:5555");

  if (rc != 0) {
    perror("zmq_bind");
    exit(1);
  }
  
  printf("loading db....\n");
  load(&root, fp);
  printf("loaded db:\n");
  inorder(root);
  putchar('\n');
  fseek(fp, 0, SEEK_SET);

  signal(SIGINT, my_function);
  while(!flag) {
    zmq_msg_init(&sms);
    zmq_msg_recv(&sms, responder, 0);
    quest = (struct msg*)zmq_msg_data(&sms);
    printf("Recieved client id %zu cash %zu and message %s\n", quest->clientId, quest->cash, quest->message);

    if ((node = find(root, quest->clientId)) == NULL) {
      // не нашли клиента, либо создаем нового, либо формируем ответ об отсутствии
      if (flock(fileno(fp), LOCK_EX) == 0) {
        printf("adding client\n");

        tmp.id = quest->clientId;
        tmp.cash = quest->cash;
        root = insert(root, &tmp);
        printf("inorder of bst:\n");
        inorder(root);
        putchar('\n');
        sprintf(ans, "OK");
        printf("ans is %s\n", ans);
        
        flock(fileno(fp), LOCK_UN);
      } else {
        printf("error(((\n");
      }      
    } else {

      if (strncmp("ADD", quest->message, 3) == 0) {
        if (flock(fileno(fp), LOCK_EX) == 0) {
          node->key.cash += strtoul(quest->message + 3, NULL, 0);
          sprintf(ans, "OK");
          printf("ans is %s\n", ans);

          flock(fileno(fp), LOCK_UN);
        } else {
          printf("error(((\n");
        }
      } else if (strncmp("RMV", quest->message, 3) == 0) {
        remCash = strtoul(quest->message + 3, NULL, 0);
        if (remCash <= node->key.cash) {
          if (flock(fileno(fp), LOCK_EX) == 0) {
            node->key.cash -= remCash;
            sprintf(ans, "OK");
            printf("ans is %s\n", ans);

            flock(fileno(fp), LOCK_UN);
          } else {
            printf("error(((\n");
          }
        } else {
          sprintf(ans, "NISHEBROD");
          printf("ans is %s\n", ans);
        }
      } else if (strncmp("STS", quest->message, 3) == 0) {
        if (flock(fileno(fp), LOCK_EX) == 0) {
          sprintf(ans, "ID %zu CSH %zu", node->key.id, node->key.cash);
          printf("ans is %s\n", ans);
          flock(fileno(fp), LOCK_UN);
        }
      } else if (strncmp("GFT", quest->message, 3) == 0) {
        if (sscanf(quest->message + 3,"%zu %zu", &friendId, &remCash) == 2) {
          if ((friend = find(root, friendId)) != NULL) {
            if (remCash <= node->key.cash) {
              if (flock(fileno(fp), LOCK_EX) == 0) {
                node->key.cash -= remCash;
                friend->key.cash += remCash;
                sprintf(ans, "OK");
                printf("ans is %s\n", ans);
                
                flock(fileno(fp), LOCK_UN);
              } else {
                printf("error(((\n");
              }
            } else {
              sprintf(ans, "NISHEBROD");
              printf("ans is %s\n", ans);
            }
          } else {
            sprintf(ans, "NOFRND");
            printf("ans is %s\n", ans);
          }
        } else {
          sprintf(ans, "ERR");
          printf("ans is %s\n", ans);
        }
          
      } else {
        sprintf(ans, "ERR");
        printf("ans is %s\n", ans);
      }

    }
    zmq_msg_close(&sms);

    zmq_msg_init_size(&reply, strlen(ans)+1);
    memcpy(zmq_msg_data(&reply), ans, strlen(ans)+1);
    zmq_msg_send(&reply, responder, 0);
    zmq_msg_close(&reply);
  }
  printf("hello\n");
  inorder(root);
  printf("b4 del\n");
  root = delete(root, quest->clientId);
  printf("deleted\n");
  inorder(root);  
  //  freopen("./db", "w", fp);
  printf("saving tree\n");
  save(root, fp);
  inorder(root);
  printf("saved tree\n");
  fclose(fp);
  
  zmq_close(responder);
  zmq_ctx_destroy(context);
  clear(root);
  printf("finished work\n");
  
  return 0;
}
