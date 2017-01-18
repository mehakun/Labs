#define _GNU_SOURCE
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

 int main(int argc, char *argv[])
 {
   if (argc < 2) {
     printf("Usage:command filename\n");
     exit(EXIT_FAILURE);
   }
   static const int BUFFSIZE = 255;
   int fd;
   pid_t cpid;
   char *filename = argv[argc - 1];
   char buffer[BUFFSIZE];
   char command[BUFFSIZE];
   fd = open(filename, O_RDONLY);

   /*   if (pipe(pipes) == -1) {
     perror("pipe");
     exit(EXIT_FAILURE);
     }*/

   cpid = fork();
   if (cpid == -1) {
     perror("fork");
     exit(EXIT_FAILURE);
   }
   if (cpid == 0) {
     int rdbyte = read(fd, buffer, BUFFSIZE);
     if ( rdbyte == -1) {
       perror("read");
       exit(EXIT_FAILURE);
     }
     buffer[rdbyte] = '\0';
     strcpy(command, argv[1]);
     strcat(command, " ");
     strcat(command, buffer);
     //3     command[strlen(command) - 4] = '\0';
     /*     for (int i = 0; i < strlen(command); i++) {
       printf("%d char code is %d\n", i, command[i]);
       }*/
     printf("command: %s\n", command);
     //     printf("command length: %lu\n", strlen(command));
     if (execlp("/bin/sh", "sh", "-c", command, NULL) == -1) {
       perror("execl");
       exit(EXIT_FAILURE);
     }
     
     exit(EXIT_SUCCESS);
   } else {
     wait(NULL);
     close(fd);
     exit(EXIT_SUCCESS);
   }
   
   return 0;
 }

