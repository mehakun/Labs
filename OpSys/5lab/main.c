#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  struct BST* root = NULL;
  struct BST* node;
  char tmp[256];
  printf("Wercome to my supa codes, this is compile-time linking\n");
  printf("insert\n");
  while (scanf("%255s", tmp) == 1) {
    root = insert(root, tmp);
    if (root) {
      printf("node with key %s was inserted\n", tmp);
    } else {
      printf("node with key %s was not inserted\n", tmp);
    }
  }
  if (root) {
    printf("tree is:\n");
    inorder(root);
  }
  
  printf("\nfind\n");
  while (scanf("%255s", tmp) == 1) {
    node = find(root, tmp);
    if (node) {
      printf("found key %s\n", node->key);
    } else {
      printf("not found :(\n");
    }
  }

  printf("\ndelete\n");
  while (scanf("%255s", tmp) == 1) {
    root = delete(root, tmp);
    if (root == NULL) {
      printf("tree is empty:(\n");
    } else {
      printf("root key after deleting is %s\n", root->key);
    }
  }
  if (root) {
    printf("tree is:\n");
    inorder(root);
    putchar('\n');
  }
  printf("clearing\n");
  clear(root);
  printf("cleared\n");
  
  return SUCCESS;
}
