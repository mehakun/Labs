#include "bst.h"

struct BST* insert(struct BST* root, char* str) {
  if (root == NULL) {
    struct BST* node = (struct BST*)malloc(sizeof(struct BST));
    if (node == NULL) {
      printf("BAD MALLOC\n");
      exit(FAILURE);
    }
    node->left = node->right = NULL;
    strcpy(node->key, str);

    return node;
  }
  
  int cmp = strcmp(root->key, str);
  
  if (cmp == 0) {
    return SUCCESS;
  } else if (cmp < 0) {
    root->left = insert(root->left, str);
  } else if (cmp > 0) {
    root->right = insert(root->right, str);
  }

  return root;
}
                       
struct BST* find(struct BST* root, char* str) {
  if (root == NULL) {
    return NULL;
  }

  int cmp = strcmp(root->key, str);
  
  if (cmp == 0) {
    return root;
  } else if (cmp < 0) {
    return find(root->left, str);
  } else if (cmp > 0) {
    return find(root->right, str);
  }

  return NULL;
}

struct BST* delete(struct BST* root, char* str) {
  if (root == NULL) {
    return root;
  }
  
  int cmp = strcmp(root->key, str);
  struct BST* tmp;
  
  if (cmp == 0) {
    if (root->left == NULL) {
      tmp = root->right;
      free(root);
      root = NULL;
      
      return tmp;
    } else if (root->right == NULL) {
      tmp = root->left;
      free(root);
      root = NULL;
      
      return tmp;
    }

    tmp = root->right;

    while (tmp->left != NULL) {
      tmp = tmp->left;
    }

    strcpy(root->key, tmp->key);
    root->right = delete(root->right, tmp->key);
    
  } else if (cmp < 0) {
    root->left = delete(root->left, str);
  } else if (cmp > 0) {
    root->right = delete(root->right, str);
  } 

  return root;
}

void inorder(struct BST* root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%s ", root->key);
    inorder(root->right);
  }
}

void clear(struct BST* root) {
  if (root != NULL) {
    clear(root->right);
    clear(root->left);
    free(root);
    root = NULL;
  }
}
