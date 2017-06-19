#include "patricia.h"

TPatriciaNode::TPatriciaNode() : bit(-1), key(), data(0), left(this), right(this){}

TPatriciaNode::TPatriciaNode(const std::string& key,
                             const unsigned long long& data = 0, const int& bit = -1,
                             TPatriciaNode* left = nullptr, TPatriciaNode* right = nullptr) {
  this->bit = bit;
  this->key = key;
  this->data = data;
  this->left = left;
  this->right = right;
}

void TPatriciaNode::SetParam(const std::string& key,
                             const unsigned long long& data, const int& bit,
                             TPatriciaNode* left, TPatriciaNode* right) {
  this->bit = bit;
  this->key = key;
  this->data = data;
  this->left = left;
  this->right = right;
}

unsigned long long TPatriciaNode::GetData() const{
  return this->data;
}

TPatricia::TPatricia() {
  root = new TPatriciaNode();
}

int TPatricia::GetBit(const std::string& key, const int& index) {
  if (index < 0) return 2;
  /*  
      unsigned int byteNum = index >> 3;
      unsigned int bitNum = index & 7;
      unsigned char symbol = key[byteNum];
      int bit = (symbol >> bitNum) & 1;
  */
  unsigned int byteNum = index * 8;
  unsigned int bitNum = index % 8;
  unsigned char symbol = key[byteNum];
  int bit = (symbol >> bitNum) % 2;

  return bit;
}

void TPatricia::print(TPatriciaNode* node, int i = 0) {
  if ((node->left->bit >= node->bit) &&
      (node->left != node) &&
      (node->left != root))
    print(node->left, i + 1);
  for (int b = 0; b < i; b++)
    putchar('\t');
  printf("%s, %d | left is %s right is %s\n", node->key.c_str(),
         node->bit, node->left->key.c_str(),
         node->right->key.c_str());
  if ((node->right->bit >= node->bit) &&
      (node->right != node) &&
      (node->right != root))
    print(node->right, i + 1);
}   

bool TPatricia::Delete(const std::string& key) {
  auto* grandpa = root;
  auto* parent = root;
  auto* tmp = parent->right;

  while (parent->bit < tmp->bit) {
    grandpa = parent;
    parent = tmp;
    tmp = GetBit(key, tmp->bit) ? tmp->right : tmp->left;
  }
  if (tmp->key != key)
    return false;

  if (tmp != parent)
    *tmp = *parent;

  if ((parent->left->bit > parent->bit) || (parent->right->bit > parent->bit)) {

    if (parent != tmp) {
      auto* leaf = parent;
      auto* parentTmp = GetBit(parent->key, parent->bit) ? parent->right : parent->left;

      while (leaf->bit < parentTmp->bit) {
        leaf = parentTmp;
        parentTmp = GetBit(parent->key, parentTmp->bit) ? parentTmp->right: parentTmp->left;
      }

      if (parent->key != parentTmp->key)
        return false;
      
      if (GetBit(parent->key, leaf->bit))
        leaf->right = tmp;
      else
        leaf->left = tmp;
    }

    if (grandpa != parent) {
      auto* child = GetBit(key, parent->bit) ? parent->left : parent->right;

      if (GetBit(key, grandpa->bit))
        grandpa->right = child;
      else
        grandpa->left = child;
    }

  } else {
    if (grandpa != parent) {
      auto* item = ((parent->left == parent->right) && (parent->left == parent)) ? grandpa :
        ((parent->left == parent) ? parent->right : parent->left);

      if (GetBit(key, grandpa->bit))
        grandpa->right = item;
      else
        grandpa->left = item;
    }
  }
  
  delete parent;
      
  return true;
}

void TPatricia::recRemove(TPatriciaNode* node) {
  if (node == nullptr) return;

  if ((node->left->bit >= node->bit) &&
      (node->left != node) &&
      (node->left != root))
    recRemove(node->left);
  if ((node->right->bit >= node->bit) &&
      (node->right != node) &&
      (node->right != root))
    recRemove(node->right);

  delete node;
}   

TPatricia::~TPatricia() {
  recRemove(root);
}

TPatriciaNode* TPatricia::Search(const std::string& key) {
  auto* parent = root;
  auto* child = root->right;

  while (parent->bit < child->bit) {
    parent = child;
    child = GetBit(key, child->bit) ? child->right : child->left;
  }
  
  return (key == child->key) ? child : nullptr;
}

bool TPatricia::Insert(const std::string& key, const unsigned long long& value) {
  auto* parent = root;
  auto* tmp = root->right;

  while (parent->bit < tmp->bit) {
    parent = tmp;
    tmp = GetBit(key, tmp->bit) ? tmp->right : tmp->left;
  }
  if (key == tmp->key)
    return false;
  
  int resBit = 0;
  while (key[resBit] == tmp->key[resBit]) resBit++;
  resBit <<= 3;
  while (GetBit(key, resBit) == GetBit(tmp->key, resBit)) resBit++;

  parent = root;
  auto* child = parent->right;

  while ((parent->bit < child->bit) && (child->bit < resBit)) {
    parent = child;
    child = GetBit(key, child->bit) ? child->right : child->left;
  }
  
  try {  
    tmp = new TPatriciaNode();
    tmp->SetParam(key, value, resBit,
                  GetBit(key, resBit) ? child : tmp, GetBit(key, resBit) ? tmp : child);
    
    if (GetBit(key, parent->bit))
      parent->right = tmp;
    else
      parent->left = tmp;

    return true;
  } catch (std::bad_alloc& ba) {
    throw;
  }
}


void TPatricia::recSer(const TPatriciaNode* node, FILE* fp) {
  if (fprintf(fp, "%s %llu %d#", node->key.c_str(), node->data, node->bit) < 0)
    throw -2;
  
  try {
    if ((node->left->bit >= node->bit) &&
        (node->left != node) &&
        (node->left != root))
      recSer(node->left, fp);
    if ((node->right->bit >= node->bit) &&
        (node->right != node) &&
        (node->right != root))
      recSer(node->right, fp);
  } catch (int num) {
    throw;
  }
}   

bool TPatricia::Serialize(const std::string& filename) {
  FILE *fp = std::fopen(filename.c_str(), "w+");
  if (!fp) {
    std::perror("ERROR");
    return false;
  }
  if (fprintf(fp, "%s", DICT_SPEC.c_str()) < 0) {
    std::perror("ERROR");
    fclose(fp);
    return false;
  }
  
  if (root->right == root) {
    if (fprintf(fp, "%s 0 -1#", EMPTY_TREE.c_str()) < 0) {
      std::perror("ERROR");
      fclose(fp);
      return false;
    }
    fclose(fp);
    return true;
  }
  try {
    recSer(root->right, fp);
    fclose(fp);
    
    return true;
  } catch (int num) {
    std::perror("ERROR");
    fclose(fp);
    return false;
  }
}

bool TPatricia::DeSerialize(const std::string& filename) {
  FILE *fp = std::fopen(filename.c_str(), "r");
  if (!fp) {
    std::perror("ERROR");
    return false;
  }

  char tmp[CHAR_LIMIT + 1];
  fgets(tmp, DICT_SPEC.length() + 1, fp);
  if (DICT_SPEC.compare(tmp) != 0) {
    printf("ERROR: Not a dictionary\n");
    return false;
  }
  
  if (root->right != root) {
    recRemove(root->right);
    root->right = root;
  }
  
  unsigned long long value;
  int bit;
  if (fscanf(fp, "%s %llu %d#", tmp, &value, &bit) < 0) {
    std::perror("ERROR");
    return false;
  }
    
  if ((tmp == EMPTY_TREE) && (value == 0) && (bit == -1))
    return true;
  
  try {
    std::string key;
    root->right = new TPatriciaNode();
    root->right->SetParam(tmp, value, bit, root, root->right);
    auto* parent = root;
    auto* child = parent->right;
      
    while (fscanf(fp, "%s %llu %d#", tmp, &value, &bit) == 3) {
      key.assign(tmp);
      while ((parent->bit < child->bit) && (child->bit < bit)) {
        parent = child;
        child = GetBit(key, child->bit) ? child->right : child->left;
      }
  
      TPatriciaNode* temp = new TPatriciaNode();
      temp->SetParam(key, value, bit,
                     GetBit(key, bit) ? child : temp, GetBit(key, bit) ? temp : child);
        
      if (GetBit(key, parent->bit))
        parent->right = temp;
      else
        parent->left = temp;
        
      parent = root;
      child = parent->right;
    }
    fclose(fp);
    return true;
      
  } catch (std::bad_alloc& ba) {
    fclose(fp);
    throw;
  }
    
}

TPatriciaNode TPatriciaNode::operator= (const TPatriciaNode& obj) {
  this->key = obj.key;
  this->data = obj.data;

  return *this;
}
