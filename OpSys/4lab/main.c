#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>
#include "general.h"

int main(int argc, char *argv[]) {
  int size, fd = 0;
  struct stat fileStat;
  
  if (argc < 2 || argc > 6) {
    handler(0);
    
  } else if (argc == 2) {
    if (strcmp(argv[1], "-help") == 0)
      handler(0);
    else if (strcmp(argv[1], "-commands") == 0) {
      handler(2); 
    } else {
      int command, from, to;
      char strToSearch[256], strToAdd[256], filename[256], readyString[256];
      filename[0] = '\0';
      
      size = atoi(argv[1]);
      checkLimit(&size);

      do {
        menu(0);
        scanf("%d", &command);

        switch (command) {
        case 0: {
          menu(5);
          if (fd) {
            if (flock(fd, LOCK_UN))
              handle_error("flock");
    
            close(fd);
          }
        
          scanf("%255s", filename);
          fd = open(filename, O_RDWR);
          if (fd == -1) {
            handle_error("open");
          }
          if (fstat(fd, &fileStat) == -1) {
            handle_error("fstat");
          }
          if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
            if (errno == EWOULDBLOCK) {
              printf("File is in usage\n");
              exit(1);
            } else {
              handle_error("flock");
            }
          }
          break;
        
        }
        case 1: {
          menu(1);
          scanf("%255s", strToSearch);
          process(readyString, strToSearch);
          search(fd, fileStat.st_size, size, readyString, strlen(readyString));
          break;
        }
        case 2: {
          menu(2);
          scanf("%d %d", &from, &to);
          print(fd, fileStat.st_size, size, from, to);
          break;
        }
        case 3: {
          menu(3);
          scanf("%255s %d", strToAdd, &from);
          process(readyString, strToAdd);
          insertSym(fd, fileStat.st_size, size, readyString, from, from + strlen(strToAdd));
          if (fstat(fd, &fileStat) == -1) {
            handle_error("fstat");
          }

          break;
        }
        case 4: {
          menu(4);
          scanf("%d %d", &from, &to);
          removeSym(fd, fileStat.st_size, size, from, from + to);
          if (fstat(fd, &fileStat) == -1) {
            handle_error("fstat");
          }

          break;
        }
        case 5: {
          getStats(fd, fileStat.st_size, size);
          break;
        }
        case 6:        
          break;
        default: {
          menu(6);
          break;
        }
        
        }
      
      } while (command != 6);
    }
  } else if (argc == 4) {
    if (strcmp(argv[3], "-stats") == 0) {
      fd = open(argv[1], O_RDWR);
      if (fd == -1) {
        handle_error("open");
      }
      if (fstat(fd, &fileStat) == -1) {
        handle_error("fstat");
      }
      if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
          printf("File is in usage\n");
          exit(1);
        } else {
          handle_error("flock");
        }
      }
      
      size = atoi(argv[2]);
      checkLimit(&size);      
      getStats(fd, fileStat.st_size, size);

      flock(fd, LOCK_UN);
    }
  } else if (argc >= 5) {
    
    if (strcmp(argv[3], "-search") == 0) {
      fd = open(argv[1], O_RDWR);
      if (fd == -1) {
        handle_error("open");
      }
      if (fstat(fd, &fileStat) == -1) {
        handle_error("fstat");
      }
      if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
          printf("File is in usage\n");
          exit(1);
        } else {
          handle_error("flock");
        }
      }
       
      char* strToSearch = (char*)malloc(sizeof(char) * strlen(argv[4]));
      process(strToSearch, argv[4]);
      printf("file to open is %s\n", argv[1]);
      printf("i will search for %s with length %lu\n", strToSearch, strlen(strToSearch));
      size = atoi(argv[2]);
      checkLimit(&size);
      search(fd, fileStat.st_size, size, strToSearch, strlen(strToSearch));
      if (flock(fd, LOCK_UN))
        handle_error("flock");
      close(fd);
    } else if (strcmp(argv[3], "-print") == 0) {
      fd = open(argv[1], O_RDWR);
      if (fd == -1) {
        handle_error("open");
      }
      if (fstat(fd, &fileStat) == -1) {
        handle_error("fstat");
      }
      if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
          printf("File is in usage\n");
          exit(1);
        } else {
          handle_error("flock");
        }
      }
       
      int from = atoi(argv[4]);
      int to = atoi(argv[5]);
      size = atoi(argv[2]);
      checkLimit(&size);
      print(fd, fileStat.st_size, size, from, to);
      if (flock(fd, LOCK_UN))
        handle_error("flock");
      close(fd);
      
    } else if (strcmp(argv[3], "-add") == 0) {
      printf("file to open is %s\n", argv[1]);
      fd = open(argv[1], O_RDWR);
      if (fd == -1) {
        handle_error("open");
      }
      if (fstat(fd, &fileStat) == -1) {
        handle_error("fstat");
      }
      if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
          printf("File is in usage\n");
          exit(1);
        } else {
          handle_error("flock");
        }
      }
       
      char* string = (char*)malloc(sizeof(char) * strlen(argv[4]));
      process(string, argv[4]);
      int from = atoi(argv[5]);
      size = atoi(argv[2]);
      checkLimit(&size);
      insertSym(fd, fileStat.st_size, size, string, from, from + strlen(string));
      if (flock(fd, LOCK_UN))
        handle_error("flock");
      close(fd);

    } else if (strcmp(argv[3], "-remove") == 0) {
      fd = open(argv[1], O_RDWR);
      if (fd == -1) {
        handle_error("open");
      }
      if (fstat(fd, &fileStat) == -1) {
        handle_error("fstat");
      }
      if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
          printf("File is in usage\n");
          exit(1);
        } else {
          handle_error("flock");
        }
      }
       
      int from = atoi(argv[4]);
      int amount = atoi(argv[5]);
      size = atoi(argv[2]);
      checkLimit(&size);
      removeSym(fd, fileStat.st_size, size, from, from + amount);
      if (flock(fd, LOCK_UN))
        handle_error("flock");
      close(fd);
      
    } else {
      handler(1);
    }
    
  } 
          
  return 0;
}
