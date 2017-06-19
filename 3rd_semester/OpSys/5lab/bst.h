#ifndef _BST_H
#define _BST_H
#define LENGTH 256
#define SUCCESS 0
#define FAILURE 1
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct BST{
  struct BST* left;
  struct BST* right;
  char key[LENGTH];
};

extern struct BST* insert(struct BST* root, char* str);
extern struct BST* find(struct BST* root, char* str);
extern struct BST* delete(struct BST* root, char* str);
extern void inorder(struct BST *root);
extern void clear(struct BST* root);

#endif /* _BST_H */
