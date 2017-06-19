#ifndef PATRICIA_H
#define PATRICIA_H

#include <string>
#include <cstdio>
#include <cstdlib>
#include <new>
static const int CHAR_LIMIT = 256;
static const std::string DICT_SPEC = "!Dict) ";
static const std::string EMPTY_TREE = "!()";

class TPatriciaNode {
 private:
  friend class TPatricia;
  int bit;
  std::string key;
  unsigned long long data;
  TPatriciaNode *left;
  TPatriciaNode *right;
  
 public:
  TPatriciaNode();
  TPatriciaNode(const std::string&, const unsigned long long&, const int&, TPatriciaNode*, TPatriciaNode*);
  void SetParam(const std::string&, const unsigned long long&, const int&, TPatriciaNode*, TPatriciaNode*);
  unsigned long long GetData() const;
  TPatriciaNode operator= (const TPatriciaNode&);

  ~TPatriciaNode(){};
};

class TPatricia {
 private:
  TPatriciaNode* root;
  int GetBit(const std::string&, const int&);
  void recRemove(TPatriciaNode*);
  void recSer(const TPatriciaNode* node, FILE* fp);
  void print(TPatriciaNode*, int);
  void DesInsert(const std::string&, const unsigned long long&, const int&);
 public:
  TPatricia();
  TPatriciaNode* Search(const std::string&);
  bool Insert(const std::string&, const unsigned long long&);
  bool Delete(const std::string&);
  bool DeSerialize(const std::string&);
  bool Serialize(const std::string&);
  ~TPatricia();
};

#endif
