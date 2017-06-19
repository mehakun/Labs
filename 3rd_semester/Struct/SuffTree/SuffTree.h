#ifndef TSUFFTREE_H
#define TSUFFTREE_H
#include <memory>
#include <string>
#include <map>
#include <utility>
#include <vector>

static const int INF = 1e9;

class TSuffTree {
 private:
  
  class TNode {
  public:
    int firstPos;
    int edgeLength;
    std::shared_ptr<TNode> parent;
    std::map<int, std::shared_ptr<TNode> > children;
    std::shared_ptr<TNode> suffLink;
    
    TNode(const int&, const int&, const std::shared_ptr<TNode>&);
  };
  
  int n, pos;
  std::vector<int> symPos;
  std::shared_ptr<TNode> setFirst(int&, const std::string&);
  
 public:
  std::shared_ptr<TNode> root;
  TSuffTree();
  void AddLetter(const int&);
  void inorder(const std::shared_ptr<TNode>&, const int&);
  void SetMs(std::vector<int>&, const std::string&);
};


#endif
