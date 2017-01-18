#ifndef AH_H
#define AH_H

#include <string>
#include <vector>
#include <memory>
#include <map>

class TFinitaAuto {
 private:
  
  class TNode {
  public:
    std::shared_ptr<TNode> fail;
    std::map<unsigned long, std::shared_ptr<TNode> > to;
    std::vector<int> out;
    TNode();
    
    ~TNode() {};
  };
  
  std::shared_ptr<TNode> root;
  std::vector<int> substrLens;
  int withoutJoker;
  
  void InitFailFunc();
  
 public:
  TFinitaAuto();
  void Build(const std::vector<std::string>&);
  void Search(const std::vector<unsigned long>&, std::vector< std::pair<int, int> >&, const int&);
    
  ~TFinitaAuto() {};
};

#endif // AH_H
