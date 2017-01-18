#ifndef _BST_H
#define _BST_H
#define LENGTH 256
#define SUCCESS 0
#define FAILURE 1
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct client {
  size_t id;
  size_t cash;
};

struct BST{
  struct BST* left;
  struct BST* right;
  struct client key;
};

extern struct BST* insert(struct BST* root, struct client* person);
extern struct BST* find(struct BST* root, size_t clientId);
extern struct BST* delete(struct BST* root, size_t clientId);
extern void inorder(struct BST *root);
extern void clear(struct BST* root);
extern void save(struct BST* root, FILE* file);
extern void load(struct BST** root, FILE* file);

#endif /* _BST_H */
