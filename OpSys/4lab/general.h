#ifndef GENERAL_H
#define GENERAL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/file.h>
#include <errno.h>
#define handle_error(msg)                             \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void handler(const int derp);
void process(char* dest, char* src);
void search(const int fd, const int fileSize,  const int RAMLimit, char* subString, const int ssSize);
void checkLimit(int* userLimit);
void print(const int fd, const int fileSize, const int RAMLimit, const int from, const int to);
void removeSym(const int fd, const int fileSize, const int RAMLimit, const int from, const int to);
void insertSym(const int fd, const int fileSize, const int RAMLimit, char* string, const int from, const int to);
void menu(const int blurp);
void getStats(const int fd, const int fileSize, const int RAMLimit);
  
#endif
