#include "bst.h"

struct BST* insert(struct BST* root, struct client* person) {
  if (root == NULL) {
    struct BST* node = (struct BST*)malloc(sizeof(struct BST));
    if (node == NULL) {
      printf("BAD MALLOC\n");
      exit(FAILURE);
    }
    node->left = node->right = NULL;
    node->key.id = person->id;
    node->key.cash = person->cash;
    
    return node;
  }
  
  
  if (person->id == root->key.id) {
    return root;
  } else if (root->key.id < person->id) {
    root->left = insert(root->left, person);
  } else if (root->key.id > person->id) {
    root->right = insert(root->right, person);
  }

  return root;
}
                       
struct BST* find(struct BST* root, size_t clientId) {
  if (root == NULL) {
    return NULL;
  }
  
  if (root->key.id == clientId) {
    return root;
  } else if (root->key.id < clientId) {
    return find(root->left, clientId);
  } else if (root->key.id > clientId) {
    return find(root->right, clientId);
  }

  return NULL;
}

struct BST* delete(struct BST* root, size_t clientId) {
  if (root == NULL) {
    return root;
  }
  
  struct BST* tmp;
  
  if (root->key.id == clientId) {
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

    root->right = delete(root->right, clientId);
    
  } else if (root->key.id < clientId) {
    root->left = delete(root->left, clientId);
  } else if (root->key.id > clientId) {
    root->right = delete(root->right, clientId);
  }    

  return root;
}

void inorder(struct BST* root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%zu %zu|", root->key.id, root->key.cash);
    inorder(root->right);
  }
}

void save(struct BST* root, FILE* file) {
  if (root != NULL) {
    char tmp[64];
    sprintf(tmp, "%zu %zu ", root->key.id, root->key.cash);
    fwrite(tmp, sizeof(char), strlen(tmp), file);
    save(root->left, file);
    save(root->right, file);
  } else {
    // derpb
  }
}

void load(struct BST** root, FILE* file) {
  struct client tmp;
  while (fscanf(file, "%zu %zu ", &tmp.id, &tmp.cash) == 2) {
    *root = insert(*root, &tmp);
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

