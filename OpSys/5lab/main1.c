#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) {
  struct BST* root = NULL;
  struct BST* node;
  void* libHandle;
  struct BST* (*find)(struct BST*, char*);
  struct BST* (*delete)(struct BST*, char*);
  struct BST* (*insert)(struct BST*, char*);
  void (*print)(struct BST*);
  void (*clear)(struct BST*);
  char tmp[256];
  char* err;
  printf("Wercome to my supa codes, this is runtime linking\n");
  libHandle = dlopen("/usr/lib/libctest.so", RTLD_LAZY);
  if (libHandle == NULL) {
    fprintf(stderr, "%s\n", dlerror());
    exit(FAILURE);
  }
  print = dlsym(libHandle, "inorder");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", err);
    exit(FAILURE);
  }
  
  printf("insert\n");
  insert = dlsym(libHandle, "insert");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", err);
    exit(FAILURE);
  }
  while (scanf("%255s", tmp) == 1) {
    root = (*insert)(root, tmp);
    if (root) {
      printf("node with key %s was inserted\n", tmp);
    } else {
      printf("node with key %s was not inserted\n", tmp);
    }
  }
  if (root) {
    printf("tree is:\n");
    (*print)(root);
  }
  
  printf("\nfind\n");
  find = dlsym(libHandle, "find");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", err);
    exit(FAILURE);
  }
  while (scanf("%255s", tmp) == 1) {
    node = (*find)(root, tmp);
    if (node) {
      printf("found key %s\n", node->key);
    } else {
      printf("not found :(\n");
    }
  }
  
  printf("\ndelete\n");
  delete = dlsym(libHandle, "delete");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", err);
    exit(FAILURE);
  }

  while (scanf("%255s", tmp) == 1) {
    root = (*delete)(root, tmp);
    if (root == NULL) {
      printf("tree is empty:(\n");
    } else {
      printf("root key after deleting is %s\n", root->key);
    }
  }
  if (root) {
    printf("tree is:\n");
    (*print)(root);
    putchar('\n');
  }
  
  clear = dlsym(libHandle, "clear");
  if ((err = dlerror()) != NULL) {
    fprintf(stderr, "%s\n", err);
    exit(FAILURE);
  }
  printf("clearing\n");
  (*clear)(root);
  printf("cleared\n");
  dlclose(libHandle);
  return SUCCESS;
}
