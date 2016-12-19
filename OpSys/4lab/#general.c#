#include "general.h"

void handler(const int derp) {
  if (derp == 0) {
    printf("usage - /PathToFile(if using command) RAMLimitInBytes Command(optional)\n");
    printf("-help to show this message\n");
    printf("-commands to show commands and their parameters\n");
  } else if (derp == 1) {
    printf("incorrect command\n");
    printf("availible ones:\n");
    printf("-stats\n");
    printf("-print From To\n");
    printf("-search SubString(special symbols can be included only with slash and correspoding symbol (i.e. /n for new line))\n");
    printf("-add string AtBytePos\n");
    printf("-remove AtBytePos NumOfSym\n");
  } else if (derp == 2) {
    printf("availible commands:\n");
    printf("-stats\n");
    printf("-print From To\n");
    printf("-search SubString(special symbols can be included only with slash and correspoding symbol (i.e. /n for new line))\n");
    printf("-add string AtBytePos\n");
    printf("-remove AtBytePos NumOfSym\n");
  }

  exit(0);
}

void process(char* dest, char* src) {
  size_t len = strlen(src) + 1;
  
  for (size_t i = 0, k = i; i < len && k < len; i++, k++) {
      if (src[i] == '/') {

        switch(src[i+1]) {
        
        case 'a': {
          dest[k] = '\a';
          break;
        }
        case 'b': {
          dest[k] = '\b';
          break;
        }
        case 'f': {
          dest[k] = '\f';
          break;
        }
        case 'n': {
          dest[k] = '\n';
          break;
        }
        case 't': {
          dest[k] = '\t';
          break;
        }
        case 'v': {
          dest[k] = '\v';
          break;
        }
        case 's': {
          dest[k] = ' ';
          break;
        }
        case 'S': {
          dest[k] = '\\';
          break;
        }
        case 'q': {
          dest[k] = '\'';
          break;
        }
        case 'Q': {
          dest[k] = '\"';
          break;
        }
        default:
          break;
        }
        if (i + 2 < len) {
          i += 2;
          k++;
        } 
        
      }
      
      dest[k] = src[i];      
  } 
  
}  


void search(const int fd, const int fileSize, const int RAMLimit, char* subString, const int ssSize) {
  int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
  int offset = 0, index = 0, bytepos = 1;
  char* addr;
  
  while(offset < fileSize) {
    addr = (char*)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
    if (addr == MAP_FAILED) {
      handle_error("mmap");
    }
      
    for (int i = 0; i < size; i++, bytepos++) {
      if (addr[i] == subString[index]) {
        i++;
        index++;
        
        for (; (index < ssSize) && (i < size); index++, i++) {
          if (subString[index] != addr[i]) {
            index = 0;
            break;
          }
        }

        if (index == ssSize) {
          printf("first entry was found at %d byte\n", bytepos);
          return;
        }
        
      }
      
    }
    
    if (munmap(addr, size) == -1) {
      handle_error("munmap");
    }
    
    offset += size;
  }
  
  printf("there is no entries in file\n");

}


void checkLimit(int* userLimit) {
  int pageSize = sysconf(_SC_PAGESIZE);
  
  if (*userLimit < pageSize) {
    printf("your limit is less than page size\n");
    printf("mmap limit will be set to page size - %d\n", pageSize);
    *userLimit = pageSize;
  } else if ((*userLimit % pageSize) != 0) {
    int count = 0;
    
    while (*userLimit > pageSize) {
      *userLimit -= pageSize;
      count++;
    }

    *userLimit = pageSize * count;
  }
  
}

void print(const int fd, const int fileSize, const int RAMLimit,
           const int from, const int to) {

  if ((from < 0) || (to < 0) || (from > to) || (to > fileSize)) {
    printf("enter different numbers\n");
    return;
  }
  
  int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
  int offset = 0, bytepos = 1;
  char* addr;
  
  while(offset < fileSize) {
    addr = (char*)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
    if (addr == MAP_FAILED) {
      handle_error("mmap");
    }

    for (int i = 0; i < size; i++, bytepos++) {
      if ((bytepos >= from) && (bytepos <= to) && (to <= fileSize)) {
        putchar(addr[i]);
      }
    }
    
    if (munmap(addr, size) == -1) {
      handle_error("munmap");
    }
    
    offset += size;
  }

  putchar('\n');
}

void insertSym(const int fd, const int fileSize, const int RAMLimit, char* string, const int from, const int to) {
  if ((from < 0) || (to < 0) || (from > to)) {
    printf("enter different numbers\n");
    return;
  }
  
  char* old = (char*)malloc(sizeof(char) * (fileSize - from));
  if (old == NULL) {
    handle_error("malloc+");
  }
  int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
  int offset = 0, bytepos = 1, k = 0;
  char* addr;
  
  while(offset < fileSize) {
    addr = (char*)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
    if (addr == MAP_FAILED) {
      handle_error("mmap");
    }

    for (int i = 0; i < size; i++, bytepos++) {
      if (bytepos >= from) {
        old[k] = addr[i];
        k++;
      }
    }
    
    if (munmap(addr, size) == -1) {
      handle_error("munmap");
    }
    
    offset += size;
  }
  
  int newFileSize = fileSize + to - from;
  if (ftruncate(fd, newFileSize)) {
    handle_error("ftruncate+");
  }

  int l = 0;
  bytepos = 1, offset = 0, k = 0;
  size = (RAMLimit > newFileSize) ? newFileSize : RAMLimit;
  
  while(offset < newFileSize) {
    addr = (char*)mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
    if (addr == MAP_FAILED) {
      handle_error("mmap");
    }

    for (int i = 0; i < size; i++, bytepos++) {
      if ((bytepos >= from) && (bytepos < to)) {
        addr[i] = string[l];
        l++;
      }
      
      if (bytepos >= to) {
        addr[i] = old[k];
        k++;
      }
    }


    if (msync(addr, size, MS_SYNC) == -1) {
      handle_error("msync");
    }
    
    if (munmap(addr, size) == -1) {
      handle_error("munmap");
    }
    
    offset += size;
  }

  free(old);
}

void removeSym(const int fd, const int fileSize, const int RAMLimit, const int from, const int to) {
  if ((from < 0) || (to < 0) || (from > to) || (to - 1 > fileSize)) {
    printf("enter different numbers\n");
    return;
  }
  int diff = (fileSize == to - 1) ? 1 : fileSize - to;
  char* old = (char*)malloc(sizeof(char) * diff);
  if (old == NULL) {
    handle_error("malloc-");
  }
  int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
  int offset = 0, bytepos = 1, k = 0;
  char* addr;
  
  while (offset < fileSize) {
    addr = (char*)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
    if (addr == MAP_FAILED) {
      handle_error("mmap");
    }

    for (int i = 0; i < size; i++, bytepos++) {
      if (bytepos >= to) {
        old[k] = addr[i];
        k++;
      }
    }
    
    if (munmap(addr, size) == -1) {
      handle_error("munmap");
    }
    
    offset += size;
  }
  
  int newFileSize = fileSize - to + from;
  if (ftruncate(fd, newFileSize)) {
    handle_error("ftruncate-");
  }

  bytepos = 1, offset = 0, k = 0;
  size = (RAMLimit > newFileSize) ? newFileSize : RAMLimit;
  
  while(offset < newFileSize) {
    addr = (char*)mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
    if (addr == MAP_FAILED) {
      handle_error("mmap");
    }

    for (int i = 0; i < size; i++, bytepos++) {
      if (bytepos >= from) {
        addr[i] = old[k];
        k++;
      }
      
    }

    if (msync(addr, size, MS_SYNC) == -1) {
      handle_error("msync");
    }
    
    if (munmap(addr, size) == -1) {
      handle_error("munmap");
    }
    
    offset += size;
  }

  free(old);
}

void menu(const int blurp) {
  switch (blurp) {
  case 0: {
    printf("avaliable commands:\n");
    printf("0) Choose file\n");
    printf("1) Search\n");
    printf("2) Print\n");
    printf("3) Add\n");
    printf("4) Remove\n");
    printf("5) Show stats\n");
    printf("6) Exit\n");
    break;
  }
  case 1: {
    printf("Enter string to search\n");
    break;
  }
  case 2: {
    printf("Enter interval borders\n");
    break;
  }
  case 3: {
    printf("Enter string to add and position where it will be added\n");
    break;
  }
  case 4: {
    printf("Enter starting position and amount of symbols to delete\n");
    break;
  }
  case 5: {
    printf("Enter filename\n");
    break;
  }
  case 6: {
    printf("wrong option\n");
    break;
  }
    
  }
}

void getStats(const int fd, const int fileSize, const int RAMLimit) {
  char* addr;
  int offset = 0;
  int bytepos = 1;
  int lines = 1;
  int size = (RAMLimit > fileSize) ? fileSize : RAMLimit;
  
  while(offset < fileSize) {
    addr = (char*)mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, fd, offset);
    if (addr == MAP_FAILED) {
      handle_error("mmap");
    }

    for (int i = 0; i < size; i++, bytepos++) {
      if (addr[i] == '\n')
        lines++;
    }
    
    if (munmap(addr, RAMLimit) == -1) {
      handle_error("munmap");
    }
    
    offset += RAMLimit;
  }

  if (lines > 1)
    lines--;
  
  printf("amount of symbols - %d\namount of lines - %d\n", fileSize, lines);
}
